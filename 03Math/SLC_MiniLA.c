#include "SLC/SLC_MiniLA.h"
#include "SLC/SLC_MiniBLAS.h"
#include "SLC/SLC_NumbersCopy.h"
#include <assert.h>

#pragma region r32_functions
void SLC_Matr32_Add(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1)
{
    assert(SLC_Array_SameSize2D(dst, src0));
    assert(SLC_Array_SameSize2D(dst, src1));
    SLC_r32_addsubs(dst->data._r32, src0->data._r32, src1->data._r32,
        ((SLC_size_t)dst->cont.i16[1])*((SLC_size_t)dst->cont.i16[2]));
}

void SLC_Matr32_ScaleAdd(SLC_PArray_t dst, SLC_PArray_t src0, const SLC_r32_t* scale0,
    SLC_PArray_t src1, const SLC_r32_t* scale1
) {
    assert(SLC_Array_SameSize2D(dst, src0));
    assert(SLC_Array_SameSize2D(dst, src1));
    SLC_r32_scaleaddsubs(
        dst->data._r32, src0->data._r32, scale0, src1->data._r32, scale1,
        ((SLC_size_t)dst->cont.i16[1])*((SLC_size_t)dst->cont.i16[2]));
}

void SLC_Matr32_Scale(SLC_PArray_t dst, SLC_PArray_t src, const SLC_r32_t *scale)
{
    assert(SLC_Array_SameSize2D(dst, src));
    SLC_r32_scalesubs(dst->data._r32, scale, src->data._r32,
        ((SLC_size_t)dst->cont.i16[1])*((SLC_size_t)dst->cont.i16[2]));
}

void SLC_Matr32_Mul(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1, SLC_PArray_t work)
{
    assert(SLC_Array_TransposedSize2D(src1, work));
    assert(SLC_Array_ValidMatrixProduct(dst, src0, src1));
    SLC_Matr32_Transpose(work, src1);
    SLC_r32_t* dst_rowhead = dst->data._r32;
    const SLC_r32_t* src0_rowhead = src0->data._r32;
    SLC_size_t dst_stride = dst->cont.i16[1];
    SLC_size_t src0_stride = src0->cont.i16[1];
    SLC_size_t work_stride = work->cont.i16[1];
    for (SLC_i16_t row = 0; row < SLC_Array_MatRows(dst); row++)
    {
        SLC_r32_t* work_rowhead = work->data._r32;
        for (SLC_i16_t column = 0; column < SLC_Array_MatColumns(dst); column++)
        {
            dst_rowhead[column] = SLC_r32_productsum(src0_rowhead, work_rowhead, src0_stride);
            work_rowhead += work_stride;
        }
        dst_rowhead += dst_stride;
        src0_rowhead += src0_stride;
    }
}

void SLC_Matr32_Transpose(SLC_PArray_t dst, SLC_PArray_t src)
{
    assert(SLC_Array_TransposedSize2D(dst, src));
    SLC_r32_t* dst_columnhead = dst->data._r32;
    const SLC_r32_t* src_rowhead = dst->data._r32;
    SLC_size_t dst_columns = SLC_Array_MatColumns(dst);
    SLC_size_t src_columns = SLC_Array_MatColumns(src);
    for (SLC_size_t dst_column = 0; dst_column < dst_columns; dst_column++)
    {
        SLC_r32_copy(dst_columnhead, dst_columns, src_rowhead, 1, src_columns);
        dst_columnhead++;
        src_rowhead += src_columns;
    }
}

void SLC_Matr32_TransConj(SLC_PArray_t dst, SLC_PArray_t src)
{
    assert(SLC_Array_TransposedSize2D(dst, src));
    SLC_r32_t* dst_columnhead = dst->data._r32;
    const SLC_r32_t* src_rowhead = dst->data._r32;
    SLC_size_t dst_columns = SLC_Array_MatColumns(dst);
    SLC_size_t src_columns = SLC_Array_MatColumns(src);
    for (SLC_size_t dst_column = 0; dst_column < dst_columns; dst_column++)
    {
        SLC_r32_copy(dst_columnhead, dst_columns, src_rowhead, 1, src_columns);
        dst_columnhead++;
        src_rowhead += src_columns;
    }
}

static SLC_i32_t SLC_Matr32_SelectPivot(SLC_PArray_t mat, SLC_size_t columns, SLC_size_t pivot_row)
{
    SLC_i32_t found = -1;
    SLC_r32_t pivot_norm_max = SLC_r32_units[0];
    SLC_size_t mat_stride = SLC_Array_MatColumns(mat);
    SLC_r32_t* pivot_ptr = mat->data._r32 + pivot_row * mat_stride + pivot_row;
    SLC_size_t rowlength = columns - pivot_row;
    const SLC_r32_t pivot_norm_threshold = SLC_r32_units[1] / (SLC_r32_t)(rowlength * 10);
    for (SLC_size_t row = pivot_row; row < columns; row++)
    {
        SLC_r32_t pivot_norm = SLC_r32_abs(*pivot_ptr) / SLC_r32_abssum(pivot_ptr, rowlength);
        if ((pivot_norm > pivot_norm_threshold) && (pivot_norm > pivot_norm_max))
        {
            found = row;
            pivot_norm_max = pivot_norm;
        }
        pivot_ptr += SLC_Array_MatColumns(mat);
    }
    return found;
}

SLC_errno_t SLC_Matr32_Inv(SLC_PArray_t dst, SLC_PArray_t src, SLC_PArray_t work)
{
    // err is to detect that src is near singular.
    SLC_errno_t err = EXIT_SUCCESS;

    // check if dst and src are same size square matrices.
    assert(SLC_Array_SameSquareMatrixSize(dst, src));
    // check work size; work.rows == src.rows + 1, work.columns == 2 * src.columns.
    assert(SLC_Array_InvWorkSize(src, work));
    do {
        SLC_size_t src_rows = SLC_Array_MatRows(src);
        SLC_size_t src_columns = SLC_Array_MatColumns(src);
        SLC_size_t work_rows = SLC_Array_MatRows(work);
        SLC_size_t work_columns = SLC_Array_MatColumns(work);
        const SLC_r32_t* src_row_head = src->data._r32;
        SLC_r32_t* work_row_head = work->data._r32;
        SLC_r32_t* pivot_ptr = work_row_head;
        SLC_r32_t* work_row_center = work_row_head + src_columns;
        SLC_r32_t* swap_buffer = work_row_head + src_rows;
        SLC_r32_t* dst_row_head = dst->data._r32;

        // fill work matrix
        for (SLC_i32_t row = 0; row < src_rows; row++)
        {
            SLC_r32_copy(work_row_head, 1, src_row_head, 1, src_columns);
            SLC_r32_copy(work_row_center, 1, SLC_r32_units, 0, src_columns);
            work_row_center[row] = SLC_r32_units[1];
            src_row_head += src_columns;
            work_row_head += work_columns;
            work_row_center += work_columns;
        }

        // calculation
        for (SLC_size_t row = 0; row < src_rows; row++)
        {
            SLC_size_t remaining_work_columns = work_columns - row;
            // pivot selection
            SLC_i32_t new_pivot_row = SLC_Matr32_SelectPivot(work, src_columns, row);
            if (new_pivot_row == -1)
            { // src is singular.
                err = SLC_ESINGULAR;
                break;
            }
            else if (row != (SLC_size_t)new_pivot_row)
            {
                SLC_r32_swap(pivot_ptr, pivot_ptr + (new_pivot_row - row) * work_columns,
                    swap_buffer, remaining_work_columns);
            }

            // normalize pivot row
            SLC_r32_t scaling = SLC_r32_units[1] / (*pivot_ptr); // reciprocal of original pivot value
            SLC_r32_scaleip(pivot_ptr, &scaling, remaining_work_columns); // scaling the pivot row

            // eliminate pivot column elements except the pivot element.
            work_row_head = work->data._r32 + row;
            for (SLC_size_t row2 = 0; row2 < src_rows; row2++)
            {
                if (row == row2)
                { // skip the pivot row
                    work_row_head += work_columns;
                    continue;
                }
                scaling = -(*work_row_head);
                SLC_r32_scaleaddip(pivot_ptr, work_row_head, &scaling, remaining_work_columns);
                work_row_head += work_columns;
            }

            // move pivot to the next position
            pivot_ptr += work_columns + 1; // move to next row, next column
            swap_buffer++; // move to next column
        }
        if (err) break;

        // copy inv-mat from work to dst
        work_row_center = work->data._r32 + src_columns;
        for (SLC_size_t row = 0; row < src_rows; row++)
        {
            SLC_r32_copy(dst_row_head, 1, work_row_center, 1, src_columns);
            work_row_center += work_columns;
            dst_row_head += src_columns;
        }
    } while (0);
    return err;
}

// solve fully determined linear equation
// left * dst = right,
// left, right: known matrix
// dst: unknown solution
SLC_errno_t SLC_Matr32_Solve(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right, SLC_PArray_t work
) {
    // unit scalar element; i.e. 1.0f for float, (1.0, 0.0) for double complex,..
    const SLC_r32_t _1 = SLC_r32_units[1];
    SLC_errno_t err = EXIT_SUCCESS;
    assert(SLC_Array_MatRows(left) == SLC_Array_MatColumns(left));
    assert(SLC_Array_MatRows(left) == SLC_Array_MatRows(right));
    assert(SLC_Array_MatRows(dst) == SLC_Array_MatColumns(left));
    assert(SLC_Array_MatColumns(dst) == SLC_Array_MatColumns(right));
    assert(SLC_Array_MatRows(work) == (SLC_Array_MatRows(left) + 1));
    assert(SLC_Array_MatColumns(work) == (SLC_Array_MatColumns(left) + SLC_Array_MatColumns(right)));
    SLC_size_t left_rows = SLC_Array_MatRows(left);
    SLC_size_t right_columns = SLC_Array_MatColumns(right);
    SLC_size_t work_columns = SLC_Array_MatColumns(work);
    SLC_r32_t* work_row_head = work->data._r32;
    SLC_r32_t* work_right_head = work_row_head + left_rows; // pointer to work matrix's region holding RHS elements.
    SLC_r32_t* swap_buffer = work_row_head + work_columns * left_rows;
    SLC_r32_t* left_row_head = left->data._r32;
    SLC_r32_t* right_row_head = right->data._r32;
    SLC_r32_t* dst_row_head = dst->data._r32;
    do {
        // setup work matrix
        for (SLC_size_t row = 0; row < left_rows; row++)
        {
            SLC_r32_copy(work_row_head, 1, left_row_head, 1, left_rows);
            SLC_r32_copy(work_row_head + left_rows, 1, right_row_head, 1, right_columns);
            work_row_head += work_columns;
        }

        // upper triangulation
        work_row_head = work->data._r32;
        for (SLC_size_t row = 0; row < left_rows; row++)
        {
            SLC_size_t active_work_columns = work_columns - row;
            SLC_r32_t pivot_scale,
                *row_head_to_eliminate = work_row_head + work_columns; // pointer to the next row of pivot element
            // select pivot row
            SLC_i32_t pivot_row = SLC_Matr32_SelectPivot(work, left_rows, row);
            if (pivot_row == -1)
            { // left matrix is singular
                err = SLC_ESINGULAR;
                break;
            }
            else if (pivot_row != row)
            {
                SLC_r32_t* new_row_head = work_row_head + (pivot_row - row) * work_columns;
                SLC_r32_swap(work_row_head, new_row_head, swap_buffer, active_work_columns);
            }

            // normalize the pivot row
            pivot_scale = _1 / (*work_row_head);
            SLC_r32_scaleip(work_row_head, &pivot_scale, active_work_columns);
            // eliminate pivot column element underneath the pivot element
            for (SLC_size_t row2 = row + 1; row2 < left_rows; row2++)
            {
                pivot_scale = -(*row_head_to_eliminate);
                SLC_r32_scaleaddip(row_head_to_eliminate, work_row_head, &pivot_scale, active_work_columns);
                row_head_to_eliminate += work_columns;
            }
            work_row_head += work_columns + 1;
            swap_buffer++;
        }
        if (err) break;

        // backward substitution
        SLC_size_t row = left_rows;
        work_row_head = work->data._r32 + left_rows * work_columns + left_rows;
        work_right_head += left_rows * work_columns;
        dst_row_head += right_columns * left_rows; // move to end (just outside)
        do {            
            --row;
            work_row_head -= (work_columns + 1);
            work_right_head -= work_columns;
            dst_row_head -= right_columns;
            for (SLC_size_t dst_column = 0; dst_column < right_columns; dst_column++)
            {
                dst_row_head[dst_column] = work_right_head[dst_column];
                for (SLC_size_t work_column = 1; work_column < left_rows; work_column++)
                {
                    dst_row_head[dst_column] -= 
                        work_right_head[dst_column + work_column * right_columns] / work_row_head[work_column];
                }
            }
        } while (row != 0);
    } while (0);
    return err;
}

SLC_errno_t SLC_Matr32_EasySolve(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right)
{
    SLC_i16_t element_size = left->cont.i16[0];
    SLC_i16_t left_columns = left->cont.i16[1];
    SLC_i16_t right_columns = right->cont.i16[1];
    SLC_4i16_t work_size = { element_size, left_columns + right_columns, left->cont.i16[2] + 1, 1 };
    SLC_PArray_t work = SLC_Array_Alloca(work_size);
    SLC_Matr32_Solve(dst, left, right, work);
}

// solve overdetermined linear equation
SLC_errno_t SLC_Matr32_EasySolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right)
{
    assert(SLC_unitsizes[(SLC_size_t)SLC_r32] == SLC_Array_UnitSize(dst));
    assert(SLC_unitsizes[(SLC_size_t)SLC_r32] == SLC_Array_UnitSize(left));
    assert(SLC_unitsizes[(SLC_size_t)SLC_r32] == SLC_Array_UnitSize(right));
    SLC_4i16_t leftT_size = { left->cont.i16[0], left->cont.i16[2], left->cont.i16[1], 1 };
    SLC_4i16_t rightT_size = { right->cont.i16[0], right->cont.i16[2], right->cont.i16[1], 1 };
    SLC_4i16_t work_size = { left->cont.i16[0], left->cont.i16[1] * 2, left->cont.i16[2] + 1, 1 };
    SLC_4i16_t leftTC_left_size = { left->cont.i16[0], left->cont.i16[1], leftT_size[2], 1 };
    SLC_4i16_t leftTC_right_size = { left->cont.i16[0], right->cont.i16[1], leftT_size[2], 1 };
    SLC_PArray_t leftT = SLC_Array_Alloc(leftT_size);
    SLC_PArray_t leftTC = SLC_Array_Alloc(leftT_size);
    SLC_PArray_t leftTC_left = SLC_Array_Alloc(leftTC_left_size);
    SLC_PArray_t rightT = SLC_Array_Alloc(rightT_size);
    SLC_PArray_t leftTC_right = SLC_Array_Alloc(leftTC_right_size);
    SLC_PArray_t work = SLC_Array_Alloc(work_size);
    SLC_errno_t err = SLC_Matr32_SolveOD(dst, left, right, leftT, leftTC, leftTC_left,
        rightT, leftTC_right, work);
    free(leftT);
    free(leftTC);
    free(leftTC_left);
    free(rightT);
    free(leftTC_right);
    free(work);
    return err;
}

SLC_errno_t SLC_Matr32_SolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right,
    SLC_PArray_t leftT, SLC_PArray_t leftTC, SLC_PArray_t leftTC_left,
    SLC_PArray_t rightT, SLC_PArray_t leftTC_right,
    SLC_PArray_t work
) {
    assert(SLC_unitsizes[(SLC_size_t)SLC_r32] == SLC_Array_UnitSize(dst));
    assert(SLC_unitsizes[(SLC_size_t)SLC_r32] == SLC_Array_UnitSize(left));
    assert(SLC_unitsizes[(SLC_size_t)SLC_r32] == SLC_Array_UnitSize(right));
    assert(SLC_Array_TransposedSize2D(left, leftT));
    assert(SLC_Array_TransposedSize2D(left, leftTC));
    assert(SLC_Array_TransposedSize2D(right, rightT));
    assert(SLC_Array_ValidMatrixProduct(leftTC_left, leftTC, left));
    assert(SLC_Array_ValidMatrixProduct(leftTC_right, leftTC, right));
    SLC_Matr32_TransConj(leftTC, left);
    SLC_Matr32_Mul(leftTC_left, leftTC, left, leftT);
    SLC_Matr32_Mul(leftTC_right, leftTC, right, rightT);
    return SLC_Matr32_Solve(dst, leftTC_left, leftTC_right, work);
}

// QR decomposition
void SLC_Matr32_QRD(SLC_PArray_t dst, SLC_PArray_t src);
#pragma endregion r32_functions

// human readable print
void SLC_Matr32_Print(FILE* out, const char* header, SLC_PArray_t mat, const char* footer)
{
    fprintf(out, "%s", header);
    fprintf(out, "%d, %d\n", mat->cont.i16[1], mat->cont.i16[2]);
    const SLC_r32_t* ptr = mat->data._r32;
    for (SLC_i16_t row = 0; row < mat->cont.i16[2]; row++)
    {
        const char* delimiter = "";
        for (SLC_i16_t column = 0; column < mat->cont.i16[1]; column++)
        {
            SLC_r32_print(out, delimiter, *ptr++);
            delimiter = ",";
        }
        fprintf(out, "\n");
    }
    fprintf(out, "%s", footer);
}
#pragma region r64_functions
void SLC_Matr64_Add(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1)
{
    assert(SLC_Array_SameSize2D(dst, src0));
    assert(SLC_Array_SameSize2D(dst, src1));
    SLC_r64_addsubs(dst->data._r64, src0->data._r64, src1->data._r64,
        ((SLC_size_t)dst->cont.i16[1])*((SLC_size_t)dst->cont.i16[2]));
}

void SLC_Matr64_ScaleAdd(SLC_PArray_t dst, SLC_PArray_t src0, const SLC_r64_t* scale0,
    SLC_PArray_t src1, const SLC_r64_t* scale1
) {
    assert(SLC_Array_SameSize2D(dst, src0));
    assert(SLC_Array_SameSize2D(dst, src1));
    SLC_r64_scaleaddsubs(
        dst->data._r64, src0->data._r64, scale0, src1->data._r64, scale1,
        ((SLC_size_t)dst->cont.i16[1])*((SLC_size_t)dst->cont.i16[2]));
}

void SLC_Matr64_Scale(SLC_PArray_t dst, SLC_PArray_t src, const SLC_r64_t *scale)
{
    assert(SLC_Array_SameSize2D(dst, src));
    SLC_r64_scalesubs(dst->data._r64, scale, src->data._r64,
        ((SLC_size_t)dst->cont.i16[1])*((SLC_size_t)dst->cont.i16[2]));
}

void SLC_Matr64_Mul(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1, SLC_PArray_t work)
{
    assert(SLC_Array_TransposedSize2D(src1, work));
    assert(SLC_Array_ValidMatrixProduct(dst, src0, src1));
    SLC_Matr64_Transpose(work, src1);
    SLC_r64_t* dst_rowhead = dst->data._r64;
    const SLC_r64_t* src0_rowhead = src0->data._r64;
    SLC_size_t dst_stride = dst->cont.i16[1];
    SLC_size_t src0_stride = src0->cont.i16[1];
    SLC_size_t work_stride = work->cont.i16[1];
    for (SLC_i16_t row = 0; row < SLC_Array_MatRows(dst); row++)
    {
        SLC_r64_t* work_rowhead = work->data._r64;
        for (SLC_i16_t column = 0; column < SLC_Array_MatColumns(dst); column++)
        {
            dst_rowhead[column] = SLC_r64_productsum(src0_rowhead, work_rowhead, src0_stride);
            work_rowhead += work_stride;
        }
        dst_rowhead += dst_stride;
        src0_rowhead += src0_stride;
    }
}

void SLC_Matr64_Transpose(SLC_PArray_t dst, SLC_PArray_t src)
{
    assert(SLC_Array_TransposedSize2D(dst, src));
    SLC_r64_t* dst_columnhead = dst->data._r64;
    const SLC_r64_t* src_rowhead = dst->data._r64;
    SLC_size_t dst_columns = SLC_Array_MatColumns(dst);
    SLC_size_t src_columns = SLC_Array_MatColumns(src);
    for (SLC_size_t dst_column = 0; dst_column < dst_columns; dst_column++)
    {
        SLC_r64_copy(dst_columnhead, dst_columns, src_rowhead, 1, src_columns);
        dst_columnhead++;
        src_rowhead += src_columns;
    }
}

void SLC_Matr64_TransConj(SLC_PArray_t dst, SLC_PArray_t src)
{
    assert(SLC_Array_TransposedSize2D(dst, src));
    SLC_r64_t* dst_columnhead = dst->data._r64;
    const SLC_r64_t* src_rowhead = dst->data._r64;
    SLC_size_t dst_columns = SLC_Array_MatColumns(dst);
    SLC_size_t src_columns = SLC_Array_MatColumns(src);
    for (SLC_size_t dst_column = 0; dst_column < dst_columns; dst_column++)
    {
        SLC_r64_copy(dst_columnhead, dst_columns, src_rowhead, 1, src_columns);
        dst_columnhead++;
        src_rowhead += src_columns;
    }
}

static SLC_i32_t SLC_Matr64_SelectPivot(SLC_PArray_t mat, SLC_size_t columns, SLC_size_t pivot_row)
{
    SLC_i32_t found = -1;
    SLC_r64_t pivot_norm_max = SLC_r64_units[0];
    SLC_size_t mat_stride = SLC_Array_MatColumns(mat);
    SLC_r64_t* pivot_ptr = mat->data._r64 + pivot_row * mat_stride + pivot_row;
    SLC_size_t rowlength = columns - pivot_row;
    const SLC_r64_t pivot_norm_threshold = SLC_r64_units[1] / (SLC_r64_t)(rowlength * 10);
    for (SLC_size_t row = pivot_row; row < columns; row++)
    {
        SLC_r64_t pivot_norm = SLC_r64_abs(*pivot_ptr) / SLC_r64_abssum(pivot_ptr, rowlength);
        if ((pivot_norm > pivot_norm_threshold) && (pivot_norm > pivot_norm_max))
        {
            found = row;
            pivot_norm_max = pivot_norm;
        }
        pivot_ptr += SLC_Array_MatColumns(mat);
    }
    return found;
}

SLC_errno_t SLC_Matr64_Inv(SLC_PArray_t dst, SLC_PArray_t src, SLC_PArray_t work)
{
    // err is to detect that src is near singular.
    SLC_errno_t err = EXIT_SUCCESS;

    // check if dst and src are same size square matrices.
    assert(SLC_Array_SameSquareMatrixSize(dst, src));
    // check work size; work.rows == src.rows + 1, work.columns == 2 * src.columns.
    assert(SLC_Array_InvWorkSize(src, work));
    do {
        SLC_size_t src_rows = SLC_Array_MatRows(src);
        SLC_size_t src_columns = SLC_Array_MatColumns(src);
        SLC_size_t work_rows = SLC_Array_MatRows(work);
        SLC_size_t work_columns = SLC_Array_MatColumns(work);
        const SLC_r64_t* src_row_head = src->data._r64;
        SLC_r64_t* work_row_head = work->data._r64;
        SLC_r64_t* pivot_ptr = work_row_head;
        SLC_r64_t* work_row_center = work_row_head + src_columns;
        SLC_r64_t* swap_buffer = work_row_head + src_rows;
        SLC_r64_t* dst_row_head = dst->data._r64;

        // fill work matrix
        for (SLC_i32_t row = 0; row < src_rows; row++)
        {
            SLC_r64_copy(work_row_head, 1, src_row_head, 1, src_columns);
            SLC_r64_copy(work_row_center, 1, SLC_r64_units, 0, src_columns);
            work_row_center[row] = SLC_r64_units[1];
            src_row_head += src_columns;
            work_row_head += work_columns;
            work_row_center += work_columns;
        }

        // calculation
        for (SLC_size_t row = 0; row < src_rows; row++)
        {
            SLC_size_t remaining_work_columns = work_columns - row;
            // pivot selection
            SLC_i32_t new_pivot_row = SLC_Matr64_SelectPivot(work, src_columns, row);
            if (new_pivot_row == -1)
            { // src is singular.
                err = SLC_ESINGULAR;
                break;
            }
            else if (row != (SLC_size_t)new_pivot_row)
            {
                SLC_r64_swap(pivot_ptr, pivot_ptr + (new_pivot_row - row) * work_columns,
                    swap_buffer, remaining_work_columns);
            }

            // normalize pivot row
            SLC_r64_t scaling = SLC_r64_units[1] / (*pivot_ptr); // reciprocal of original pivot value
            SLC_r64_scaleip(pivot_ptr, &scaling, remaining_work_columns); // scaling the pivot row

            // eliminate pivot column elements except the pivot element.
            work_row_head = work->data._r64 + row;
            for (SLC_size_t row2 = 0; row2 < src_rows; row2++)
            {
                if (row == row2)
                { // skip the pivot row
                    work_row_head += work_columns;
                    continue;
                }
                scaling = -(*work_row_head);
                SLC_r64_scaleaddip(pivot_ptr, work_row_head, &scaling, remaining_work_columns);
                work_row_head += work_columns;
            }

            // move pivot to the next position
            pivot_ptr += work_columns + 1; // move to next row, next column
            swap_buffer++; // move to next column
        }
        if (err) break;

        // copy inv-mat from work to dst
        work_row_center = work->data._r64 + src_columns;
        for (SLC_size_t row = 0; row < src_rows; row++)
        {
            SLC_r64_copy(dst_row_head, 1, work_row_center, 1, src_columns);
            work_row_center += work_columns;
            dst_row_head += src_columns;
        }
    } while (0);
    return err;
}

// solve fully determined linear equation
// left * dst = right,
// left, right: known matrix
// dst: unknown solution
SLC_errno_t SLC_Matr64_Solve(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right, SLC_PArray_t work
) {
    // unit scalar element; i.e. 1.0f for float, (1.0, 0.0) for double complex,..
    const SLC_r64_t _1 = SLC_r64_units[1];
    SLC_errno_t err = EXIT_SUCCESS;
    assert(SLC_Array_MatRows(left) == SLC_Array_MatColumns(left));
    assert(SLC_Array_MatRows(left) == SLC_Array_MatRows(right));
    assert(SLC_Array_MatRows(dst) == SLC_Array_MatColumns(left));
    assert(SLC_Array_MatColumns(dst) == SLC_Array_MatColumns(right));
    assert(SLC_Array_MatRows(work) == (SLC_Array_MatRows(left) + 1));
    assert(SLC_Array_MatColumns(work) == (SLC_Array_MatColumns(left) + SLC_Array_MatColumns(right)));
    SLC_size_t left_rows = SLC_Array_MatRows(left);
    SLC_size_t right_columns = SLC_Array_MatColumns(right);
    SLC_size_t work_columns = SLC_Array_MatColumns(work);
    SLC_r64_t* work_row_head = work->data._r64;
    SLC_r64_t* work_right_head = work_row_head + left_rows; // pointer to work matrix's region holding RHS elements.
    SLC_r64_t* swap_buffer = work_row_head + work_columns * left_rows;
    SLC_r64_t* left_row_head = left->data._r64;
    SLC_r64_t* right_row_head = right->data._r64;
    SLC_r64_t* dst_row_head = dst->data._r64;
    do {
        // setup work matrix
        for (SLC_size_t row = 0; row < left_rows; row++)
        {
            SLC_r64_copy(work_row_head, 1, left_row_head, 1, left_rows);
            SLC_r64_copy(work_row_head + left_rows, 1, right_row_head, 1, right_columns);
            work_row_head += work_columns;
        }

        // upper triangulation
        work_row_head = work->data._r64;
        for (SLC_size_t row = 0; row < left_rows; row++)
        {
            SLC_size_t active_work_columns = work_columns - row;
            SLC_r64_t pivot_scale,
                *row_head_to_eliminate = work_row_head + work_columns; // pointer to the next row of pivot element
            // select pivot row
            SLC_i32_t pivot_row = SLC_Matr64_SelectPivot(work, left_rows, row);
            if (pivot_row == -1)
            { // left matrix is singular
                err = SLC_ESINGULAR;
                break;
            }
            else if (pivot_row != row)
            {
                SLC_r64_t* new_row_head = work_row_head + (pivot_row - row) * work_columns;
                SLC_r64_swap(work_row_head, new_row_head, swap_buffer, active_work_columns);
            }

            // normalize the pivot row
            pivot_scale = _1 / (*work_row_head);
            SLC_r64_scaleip(work_row_head, &pivot_scale, active_work_columns);
            // eliminate pivot column element underneath the pivot element
            for (SLC_size_t row2 = row + 1; row2 < left_rows; row2++)
            {
                pivot_scale = -(*row_head_to_eliminate);
                SLC_r64_scaleaddip(row_head_to_eliminate, work_row_head, &pivot_scale, active_work_columns);
                row_head_to_eliminate += work_columns;
            }
            work_row_head += work_columns + 1;
            swap_buffer++;
        }
        if (err) break;

        // backward substitution
        SLC_size_t row = left_rows;
        work_row_head = work->data._r64 + left_rows * work_columns + left_rows;
        work_right_head += left_rows * work_columns;
        dst_row_head += right_columns * left_rows; // move to end (just outside)
        do {            
            --row;
            work_row_head -= (work_columns + 1);
            work_right_head -= work_columns;
            dst_row_head -= right_columns;
            for (SLC_size_t dst_column = 0; dst_column < right_columns; dst_column++)
            {
                dst_row_head[dst_column] = work_right_head[dst_column];
                for (SLC_size_t work_column = 1; work_column < left_rows; work_column++)
                {
                    dst_row_head[dst_column] -= 
                        work_right_head[dst_column + work_column * right_columns] / work_row_head[work_column];
                }
            }
        } while (row != 0);
    } while (0);
    return err;
}

SLC_errno_t SLC_Matr64_EasySolve(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right)
{
    SLC_i16_t element_size = left->cont.i16[0];
    SLC_i16_t left_columns = left->cont.i16[1];
    SLC_i16_t right_columns = right->cont.i16[1];
    SLC_4i16_t work_size = { element_size, left_columns + right_columns, left->cont.i16[2] + 1, 1 };
    SLC_PArray_t work = SLC_Array_Alloca(work_size);
    SLC_Matr64_Solve(dst, left, right, work);
}

// solve overdetermined linear equation
SLC_errno_t SLC_Matr64_EasySolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right)
{
    assert(SLC_unitsizes[(SLC_size_t)SLC_r64] == SLC_Array_UnitSize(dst));
    assert(SLC_unitsizes[(SLC_size_t)SLC_r64] == SLC_Array_UnitSize(left));
    assert(SLC_unitsizes[(SLC_size_t)SLC_r64] == SLC_Array_UnitSize(right));
    SLC_4i16_t leftT_size = { left->cont.i16[0], left->cont.i16[2], left->cont.i16[1], 1 };
    SLC_4i16_t rightT_size = { right->cont.i16[0], right->cont.i16[2], right->cont.i16[1], 1 };
    SLC_4i16_t work_size = { left->cont.i16[0], left->cont.i16[1] * 2, left->cont.i16[2] + 1, 1 };
    SLC_4i16_t leftTC_left_size = { left->cont.i16[0], left->cont.i16[1], leftT_size[2], 1 };
    SLC_4i16_t leftTC_right_size = { left->cont.i16[0], right->cont.i16[1], leftT_size[2], 1 };
    SLC_PArray_t leftT = SLC_Array_Alloc(leftT_size);
    SLC_PArray_t leftTC = SLC_Array_Alloc(leftT_size);
    SLC_PArray_t leftTC_left = SLC_Array_Alloc(leftTC_left_size);
    SLC_PArray_t rightT = SLC_Array_Alloc(rightT_size);
    SLC_PArray_t leftTC_right = SLC_Array_Alloc(leftTC_right_size);
    SLC_PArray_t work = SLC_Array_Alloc(work_size);
    SLC_errno_t err = SLC_Matr64_SolveOD(dst, left, right, leftT, leftTC, leftTC_left,
        rightT, leftTC_right, work);
    free(leftT);
    free(leftTC);
    free(leftTC_left);
    free(rightT);
    free(leftTC_right);
    free(work);
    return err;
}

SLC_errno_t SLC_Matr64_SolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right,
    SLC_PArray_t leftT, SLC_PArray_t leftTC, SLC_PArray_t leftTC_left,
    SLC_PArray_t rightT, SLC_PArray_t leftTC_right,
    SLC_PArray_t work
) {
    assert(SLC_unitsizes[(SLC_size_t)SLC_r64] == SLC_Array_UnitSize(dst));
    assert(SLC_unitsizes[(SLC_size_t)SLC_r64] == SLC_Array_UnitSize(left));
    assert(SLC_unitsizes[(SLC_size_t)SLC_r64] == SLC_Array_UnitSize(right));
    assert(SLC_Array_TransposedSize2D(left, leftT));
    assert(SLC_Array_TransposedSize2D(left, leftTC));
    assert(SLC_Array_TransposedSize2D(right, rightT));
    assert(SLC_Array_ValidMatrixProduct(leftTC_left, leftTC, left));
    assert(SLC_Array_ValidMatrixProduct(leftTC_right, leftTC, right));
    SLC_Matr64_TransConj(leftTC, left);
    SLC_Matr64_Mul(leftTC_left, leftTC, left, leftT);
    SLC_Matr64_Mul(leftTC_right, leftTC, right, rightT);
    return SLC_Matr64_Solve(dst, leftTC_left, leftTC_right, work);
}

// QR decomposition
void SLC_Matr64_QRD(SLC_PArray_t dst, SLC_PArray_t src);
#pragma endregion r64_functions

// human readable print
void SLC_Matr64_Print(FILE* out, const char* header, SLC_PArray_t mat, const char* footer)
{
    fprintf(out, "%s", header);
    fprintf(out, "%d, %d\n", mat->cont.i16[1], mat->cont.i16[2]);
    const SLC_r64_t* ptr = mat->data._r64;
    for (SLC_i16_t row = 0; row < mat->cont.i16[2]; row++)
    {
        const char* delimiter = "";
        for (SLC_i16_t column = 0; column < mat->cont.i16[1]; column++)
        {
            SLC_r64_print(out, delimiter, *ptr++);
            delimiter = ",";
        }
        fprintf(out, "\n");
    }
    fprintf(out, "%s", footer);
}
#pragma region c64_functions
void SLC_Matc64_Add(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1)
{
    assert(SLC_Array_SameSize2D(dst, src0));
    assert(SLC_Array_SameSize2D(dst, src1));
    SLC_c64_addsubs(dst->data._c64, src0->data._c64, src1->data._c64,
        ((SLC_size_t)dst->cont.i16[1])*((SLC_size_t)dst->cont.i16[2]));
}

void SLC_Matc64_ScaleAdd(SLC_PArray_t dst, SLC_PArray_t src0, const SLC_c64_t* scale0,
    SLC_PArray_t src1, const SLC_c64_t* scale1
) {
    assert(SLC_Array_SameSize2D(dst, src0));
    assert(SLC_Array_SameSize2D(dst, src1));
    SLC_c64_scaleaddsubs(
        dst->data._c64, src0->data._c64, scale0, src1->data._c64, scale1,
        ((SLC_size_t)dst->cont.i16[1])*((SLC_size_t)dst->cont.i16[2]));
}

void SLC_Matc64_Scale(SLC_PArray_t dst, SLC_PArray_t src, const SLC_c64_t *scale)
{
    assert(SLC_Array_SameSize2D(dst, src));
    SLC_c64_scalesubs(dst->data._c64, scale, src->data._c64,
        ((SLC_size_t)dst->cont.i16[1])*((SLC_size_t)dst->cont.i16[2]));
}

void SLC_Matc64_Mul(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1, SLC_PArray_t work)
{
    assert(SLC_Array_TransposedSize2D(src1, work));
    assert(SLC_Array_ValidMatrixProduct(dst, src0, src1));
    SLC_Matc64_Transpose(work, src1);
    SLC_c64_t* dst_rowhead = dst->data._c64;
    const SLC_c64_t* src0_rowhead = src0->data._c64;
    SLC_size_t dst_stride = dst->cont.i16[1];
    SLC_size_t src0_stride = src0->cont.i16[1];
    SLC_size_t work_stride = work->cont.i16[1];
    for (SLC_i16_t row = 0; row < SLC_Array_MatRows(dst); row++)
    {
        SLC_c64_t* work_rowhead = work->data._c64;
        for (SLC_i16_t column = 0; column < SLC_Array_MatColumns(dst); column++)
        {
            dst_rowhead[column] = SLC_c64_productsum(src0_rowhead, work_rowhead, src0_stride);
            work_rowhead += work_stride;
        }
        dst_rowhead += dst_stride;
        src0_rowhead += src0_stride;
    }
}

void SLC_Matc64_Transpose(SLC_PArray_t dst, SLC_PArray_t src)
{
    assert(SLC_Array_TransposedSize2D(dst, src));
    SLC_c64_t* dst_columnhead = dst->data._c64;
    const SLC_c64_t* src_rowhead = dst->data._c64;
    SLC_size_t dst_columns = SLC_Array_MatColumns(dst);
    SLC_size_t src_columns = SLC_Array_MatColumns(src);
    for (SLC_size_t dst_column = 0; dst_column < dst_columns; dst_column++)
    {
        SLC_c64_copy(dst_columnhead, dst_columns, src_rowhead, 1, src_columns);
        dst_columnhead++;
        src_rowhead += src_columns;
    }
}

void SLC_Matc64_TransConj(SLC_PArray_t dst, SLC_PArray_t src)
{
    assert(SLC_Array_TransposedSize2D(dst, src));
    SLC_c64_t* dst_columnhead = dst->data._c64;
    const SLC_c64_t* src_rowhead = dst->data._c64;
    SLC_size_t dst_columns = SLC_Array_MatColumns(dst);
    SLC_size_t src_columns = SLC_Array_MatColumns(src);
    for (SLC_size_t dst_column = 0; dst_column < dst_columns; dst_column++)
    {
        SLC_c64_copy(dst_columnhead, dst_columns, src_rowhead, 1, src_columns);
        dst_columnhead++;
        src_rowhead += src_columns;
    }
}

static SLC_i32_t SLC_Matc64_SelectPivot(SLC_PArray_t mat, SLC_size_t columns, SLC_size_t pivot_row)
{
    SLC_i32_t found = -1;
    SLC_r32_t pivot_norm_max = SLC_r32_units[0];
    SLC_size_t mat_stride = SLC_Array_MatColumns(mat);
    SLC_c64_t* pivot_ptr = mat->data._c64 + pivot_row * mat_stride + pivot_row;
    SLC_size_t rowlength = columns - pivot_row;
    const SLC_r32_t pivot_norm_threshold = SLC_r32_units[1] / (SLC_r32_t)(rowlength * 10);
    for (SLC_size_t row = pivot_row; row < columns; row++)
    {
        SLC_r32_t pivot_norm = SLC_c64_abs(*pivot_ptr) / SLC_c64_abssum(pivot_ptr, rowlength);
        if ((pivot_norm > pivot_norm_threshold) && (pivot_norm > pivot_norm_max))
        {
            found = row;
            pivot_norm_max = pivot_norm;
        }
        pivot_ptr += SLC_Array_MatColumns(mat);
    }
    return found;
}

SLC_errno_t SLC_Matc64_Inv(SLC_PArray_t dst, SLC_PArray_t src, SLC_PArray_t work)
{
    // err is to detect that src is near singular.
    SLC_errno_t err = EXIT_SUCCESS;

    // check if dst and src are same size square matrices.
    assert(SLC_Array_SameSquareMatrixSize(dst, src));
    // check work size; work.rows == src.rows + 1, work.columns == 2 * src.columns.
    assert(SLC_Array_InvWorkSize(src, work));
    do {
        SLC_size_t src_rows = SLC_Array_MatRows(src);
        SLC_size_t src_columns = SLC_Array_MatColumns(src);
        SLC_size_t work_rows = SLC_Array_MatRows(work);
        SLC_size_t work_columns = SLC_Array_MatColumns(work);
        const SLC_c64_t* src_row_head = src->data._c64;
        SLC_c64_t* work_row_head = work->data._c64;
        SLC_c64_t* pivot_ptr = work_row_head;
        SLC_c64_t* work_row_center = work_row_head + src_columns;
        SLC_c64_t* swap_buffer = work_row_head + src_rows;
        SLC_c64_t* dst_row_head = dst->data._c64;

        // fill work matrix
        for (SLC_i32_t row = 0; row < src_rows; row++)
        {
            SLC_c64_copy(work_row_head, 1, src_row_head, 1, src_columns);
            SLC_c64_copy(work_row_center, 1, SLC_c64_units, 0, src_columns);
            work_row_center[row] = SLC_c64_units[1];
            src_row_head += src_columns;
            work_row_head += work_columns;
            work_row_center += work_columns;
        }

        // calculation
        for (SLC_size_t row = 0; row < src_rows; row++)
        {
            SLC_size_t remaining_work_columns = work_columns - row;
            // pivot selection
            SLC_i32_t new_pivot_row = SLC_Matc64_SelectPivot(work, src_columns, row);
            if (new_pivot_row == -1)
            { // src is singular.
                err = SLC_ESINGULAR;
                break;
            }
            else if (row != (SLC_size_t)new_pivot_row)
            {
                SLC_c64_swap(pivot_ptr, pivot_ptr + (new_pivot_row - row) * work_columns,
                    swap_buffer, remaining_work_columns);
            }

            // normalize pivot row
            SLC_c64_t scaling = SLC_c64_units[1] / (*pivot_ptr); // reciprocal of original pivot value
            SLC_c64_scaleip(pivot_ptr, &scaling, remaining_work_columns); // scaling the pivot row

            // eliminate pivot column elements except the pivot element.
            work_row_head = work->data._c64 + row;
            for (SLC_size_t row2 = 0; row2 < src_rows; row2++)
            {
                if (row == row2)
                { // skip the pivot row
                    work_row_head += work_columns;
                    continue;
                }
                scaling = -(*work_row_head);
                SLC_c64_scaleaddip(pivot_ptr, work_row_head, &scaling, remaining_work_columns);
                work_row_head += work_columns;
            }

            // move pivot to the next position
            pivot_ptr += work_columns + 1; // move to next row, next column
            swap_buffer++; // move to next column
        }
        if (err) break;

        // copy inv-mat from work to dst
        work_row_center = work->data._c64 + src_columns;
        for (SLC_size_t row = 0; row < src_rows; row++)
        {
            SLC_c64_copy(dst_row_head, 1, work_row_center, 1, src_columns);
            work_row_center += work_columns;
            dst_row_head += src_columns;
        }
    } while (0);
    return err;
}

// solve fully determined linear equation
// left * dst = right,
// left, right: known matrix
// dst: unknown solution
SLC_errno_t SLC_Matc64_Solve(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right, SLC_PArray_t work
) {
    // unit scalar element; i.e. 1.0f for float, (1.0, 0.0) for double complex,..
    const SLC_c64_t _1 = SLC_c64_units[1];
    SLC_errno_t err = EXIT_SUCCESS;
    assert(SLC_Array_MatRows(left) == SLC_Array_MatColumns(left));
    assert(SLC_Array_MatRows(left) == SLC_Array_MatRows(right));
    assert(SLC_Array_MatRows(dst) == SLC_Array_MatColumns(left));
    assert(SLC_Array_MatColumns(dst) == SLC_Array_MatColumns(right));
    assert(SLC_Array_MatRows(work) == (SLC_Array_MatRows(left) + 1));
    assert(SLC_Array_MatColumns(work) == (SLC_Array_MatColumns(left) + SLC_Array_MatColumns(right)));
    SLC_size_t left_rows = SLC_Array_MatRows(left);
    SLC_size_t right_columns = SLC_Array_MatColumns(right);
    SLC_size_t work_columns = SLC_Array_MatColumns(work);
    SLC_c64_t* work_row_head = work->data._c64;
    SLC_c64_t* work_right_head = work_row_head + left_rows; // pointer to work matrix's region holding RHS elements.
    SLC_c64_t* swap_buffer = work_row_head + work_columns * left_rows;
    SLC_c64_t* left_row_head = left->data._c64;
    SLC_c64_t* right_row_head = right->data._c64;
    SLC_c64_t* dst_row_head = dst->data._c64;
    do {
        // setup work matrix
        for (SLC_size_t row = 0; row < left_rows; row++)
        {
            SLC_c64_copy(work_row_head, 1, left_row_head, 1, left_rows);
            SLC_c64_copy(work_row_head + left_rows, 1, right_row_head, 1, right_columns);
            work_row_head += work_columns;
        }

        // upper triangulation
        work_row_head = work->data._c64;
        for (SLC_size_t row = 0; row < left_rows; row++)
        {
            SLC_size_t active_work_columns = work_columns - row;
            SLC_c64_t pivot_scale,
                *row_head_to_eliminate = work_row_head + work_columns; // pointer to the next row of pivot element
            // select pivot row
            SLC_i32_t pivot_row = SLC_Matc64_SelectPivot(work, left_rows, row);
            if (pivot_row == -1)
            { // left matrix is singular
                err = SLC_ESINGULAR;
                break;
            }
            else if (pivot_row != row)
            {
                SLC_c64_t* new_row_head = work_row_head + (pivot_row - row) * work_columns;
                SLC_c64_swap(work_row_head, new_row_head, swap_buffer, active_work_columns);
            }

            // normalize the pivot row
            pivot_scale = _1 / (*work_row_head);
            SLC_c64_scaleip(work_row_head, &pivot_scale, active_work_columns);
            // eliminate pivot column element underneath the pivot element
            for (SLC_size_t row2 = row + 1; row2 < left_rows; row2++)
            {
                pivot_scale = -(*row_head_to_eliminate);
                SLC_c64_scaleaddip(row_head_to_eliminate, work_row_head, &pivot_scale, active_work_columns);
                row_head_to_eliminate += work_columns;
            }
            work_row_head += work_columns + 1;
            swap_buffer++;
        }
        if (err) break;

        // backward substitution
        SLC_size_t row = left_rows;
        work_row_head = work->data._c64 + left_rows * work_columns + left_rows;
        work_right_head += left_rows * work_columns;
        dst_row_head += right_columns * left_rows; // move to end (just outside)
        do {            
            --row;
            work_row_head -= (work_columns + 1);
            work_right_head -= work_columns;
            dst_row_head -= right_columns;
            for (SLC_size_t dst_column = 0; dst_column < right_columns; dst_column++)
            {
                dst_row_head[dst_column] = work_right_head[dst_column];
                for (SLC_size_t work_column = 1; work_column < left_rows; work_column++)
                {
                    dst_row_head[dst_column] -= 
                        work_right_head[dst_column + work_column * right_columns] / work_row_head[work_column];
                }
            }
        } while (row != 0);
    } while (0);
    return err;
}

SLC_errno_t SLC_Matc64_EasySolve(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right)
{
    SLC_i16_t element_size = left->cont.i16[0];
    SLC_i16_t left_columns = left->cont.i16[1];
    SLC_i16_t right_columns = right->cont.i16[1];
    SLC_4i16_t work_size = { element_size, left_columns + right_columns, left->cont.i16[2] + 1, 1 };
    SLC_PArray_t work = SLC_Array_Alloca(work_size);
    SLC_Matc64_Solve(dst, left, right, work);
}

// solve overdetermined linear equation
SLC_errno_t SLC_Matc64_EasySolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right)
{
    assert(SLC_unitsizes[(SLC_size_t)SLC_c64] == SLC_Array_UnitSize(dst));
    assert(SLC_unitsizes[(SLC_size_t)SLC_c64] == SLC_Array_UnitSize(left));
    assert(SLC_unitsizes[(SLC_size_t)SLC_c64] == SLC_Array_UnitSize(right));
    SLC_4i16_t leftT_size = { left->cont.i16[0], left->cont.i16[2], left->cont.i16[1], 1 };
    SLC_4i16_t rightT_size = { right->cont.i16[0], right->cont.i16[2], right->cont.i16[1], 1 };
    SLC_4i16_t work_size = { left->cont.i16[0], left->cont.i16[1] * 2, left->cont.i16[2] + 1, 1 };
    SLC_4i16_t leftTC_left_size = { left->cont.i16[0], left->cont.i16[1], leftT_size[2], 1 };
    SLC_4i16_t leftTC_right_size = { left->cont.i16[0], right->cont.i16[1], leftT_size[2], 1 };
    SLC_PArray_t leftT = SLC_Array_Alloc(leftT_size);
    SLC_PArray_t leftTC = SLC_Array_Alloc(leftT_size);
    SLC_PArray_t leftTC_left = SLC_Array_Alloc(leftTC_left_size);
    SLC_PArray_t rightT = SLC_Array_Alloc(rightT_size);
    SLC_PArray_t leftTC_right = SLC_Array_Alloc(leftTC_right_size);
    SLC_PArray_t work = SLC_Array_Alloc(work_size);
    SLC_errno_t err = SLC_Matc64_SolveOD(dst, left, right, leftT, leftTC, leftTC_left,
        rightT, leftTC_right, work);
    free(leftT);
    free(leftTC);
    free(leftTC_left);
    free(rightT);
    free(leftTC_right);
    free(work);
    return err;
}

SLC_errno_t SLC_Matc64_SolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right,
    SLC_PArray_t leftT, SLC_PArray_t leftTC, SLC_PArray_t leftTC_left,
    SLC_PArray_t rightT, SLC_PArray_t leftTC_right,
    SLC_PArray_t work
) {
    assert(SLC_unitsizes[(SLC_size_t)SLC_c64] == SLC_Array_UnitSize(dst));
    assert(SLC_unitsizes[(SLC_size_t)SLC_c64] == SLC_Array_UnitSize(left));
    assert(SLC_unitsizes[(SLC_size_t)SLC_c64] == SLC_Array_UnitSize(right));
    assert(SLC_Array_TransposedSize2D(left, leftT));
    assert(SLC_Array_TransposedSize2D(left, leftTC));
    assert(SLC_Array_TransposedSize2D(right, rightT));
    assert(SLC_Array_ValidMatrixProduct(leftTC_left, leftTC, left));
    assert(SLC_Array_ValidMatrixProduct(leftTC_right, leftTC, right));
    SLC_Matc64_TransConj(leftTC, left);
    SLC_Matc64_Mul(leftTC_left, leftTC, left, leftT);
    SLC_Matc64_Mul(leftTC_right, leftTC, right, rightT);
    return SLC_Matc64_Solve(dst, leftTC_left, leftTC_right, work);
}

// QR decomposition
void SLC_Matc64_QRD(SLC_PArray_t dst, SLC_PArray_t src);
#pragma endregion c64_functions

// human readable print
void SLC_Matc64_Print(FILE* out, const char* header, SLC_PArray_t mat, const char* footer)
{
    fprintf(out, "%s", header);
    fprintf(out, "%d, %d\n", mat->cont.i16[1], mat->cont.i16[2]);
    const SLC_c64_t* ptr = mat->data._c64;
    for (SLC_i16_t row = 0; row < mat->cont.i16[2]; row++)
    {
        const char* delimiter = "";
        for (SLC_i16_t column = 0; column < mat->cont.i16[1]; column++)
        {
            SLC_c64_print(out, delimiter, *ptr++);
            delimiter = ",";
        }
        fprintf(out, "\n");
    }
    fprintf(out, "%s", footer);
}
#pragma region c128_functions
void SLC_Matc128_Add(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1)
{
    assert(SLC_Array_SameSize2D(dst, src0));
    assert(SLC_Array_SameSize2D(dst, src1));
    SLC_c128_addsubs(dst->data._c128, src0->data._c128, src1->data._c128,
        ((SLC_size_t)dst->cont.i16[1])*((SLC_size_t)dst->cont.i16[2]));
}

void SLC_Matc128_ScaleAdd(SLC_PArray_t dst, SLC_PArray_t src0, const SLC_c128_t* scale0,
    SLC_PArray_t src1, const SLC_c128_t* scale1
) {
    assert(SLC_Array_SameSize2D(dst, src0));
    assert(SLC_Array_SameSize2D(dst, src1));
    SLC_c128_scaleaddsubs(
        dst->data._c128, src0->data._c128, scale0, src1->data._c128, scale1,
        ((SLC_size_t)dst->cont.i16[1])*((SLC_size_t)dst->cont.i16[2]));
}

void SLC_Matc128_Scale(SLC_PArray_t dst, SLC_PArray_t src, const SLC_c128_t *scale)
{
    assert(SLC_Array_SameSize2D(dst, src));
    SLC_c128_scalesubs(dst->data._c128, scale, src->data._c128,
        ((SLC_size_t)dst->cont.i16[1])*((SLC_size_t)dst->cont.i16[2]));
}

void SLC_Matc128_Mul(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1, SLC_PArray_t work)
{
    assert(SLC_Array_TransposedSize2D(src1, work));
    assert(SLC_Array_ValidMatrixProduct(dst, src0, src1));
    SLC_Matc128_Transpose(work, src1);
    SLC_c128_t* dst_rowhead = dst->data._c128;
    const SLC_c128_t* src0_rowhead = src0->data._c128;
    SLC_size_t dst_stride = dst->cont.i16[1];
    SLC_size_t src0_stride = src0->cont.i16[1];
    SLC_size_t work_stride = work->cont.i16[1];
    for (SLC_i16_t row = 0; row < SLC_Array_MatRows(dst); row++)
    {
        SLC_c128_t* work_rowhead = work->data._c128;
        for (SLC_i16_t column = 0; column < SLC_Array_MatColumns(dst); column++)
        {
            dst_rowhead[column] = SLC_c128_productsum(src0_rowhead, work_rowhead, src0_stride);
            work_rowhead += work_stride;
        }
        dst_rowhead += dst_stride;
        src0_rowhead += src0_stride;
    }
}

void SLC_Matc128_Transpose(SLC_PArray_t dst, SLC_PArray_t src)
{
    assert(SLC_Array_TransposedSize2D(dst, src));
    SLC_c128_t* dst_columnhead = dst->data._c128;
    const SLC_c128_t* src_rowhead = dst->data._c128;
    SLC_size_t dst_columns = SLC_Array_MatColumns(dst);
    SLC_size_t src_columns = SLC_Array_MatColumns(src);
    for (SLC_size_t dst_column = 0; dst_column < dst_columns; dst_column++)
    {
        SLC_c128_copy(dst_columnhead, dst_columns, src_rowhead, 1, src_columns);
        dst_columnhead++;
        src_rowhead += src_columns;
    }
}

void SLC_Matc128_TransConj(SLC_PArray_t dst, SLC_PArray_t src)
{
    assert(SLC_Array_TransposedSize2D(dst, src));
    SLC_c128_t* dst_columnhead = dst->data._c128;
    const SLC_c128_t* src_rowhead = dst->data._c128;
    SLC_size_t dst_columns = SLC_Array_MatColumns(dst);
    SLC_size_t src_columns = SLC_Array_MatColumns(src);
    for (SLC_size_t dst_column = 0; dst_column < dst_columns; dst_column++)
    {
        SLC_c128_copy(dst_columnhead, dst_columns, src_rowhead, 1, src_columns);
        dst_columnhead++;
        src_rowhead += src_columns;
    }
}

static SLC_i32_t SLC_Matc128_SelectPivot(SLC_PArray_t mat, SLC_size_t columns, SLC_size_t pivot_row)
{
    SLC_i32_t found = -1;
    SLC_r64_t pivot_norm_max = SLC_r64_units[0];
    SLC_size_t mat_stride = SLC_Array_MatColumns(mat);
    SLC_c128_t* pivot_ptr = mat->data._c128 + pivot_row * mat_stride + pivot_row;
    SLC_size_t rowlength = columns - pivot_row;
    const SLC_r64_t pivot_norm_threshold = SLC_r64_units[1] / (SLC_r64_t)(rowlength * 10);
    for (SLC_size_t row = pivot_row; row < columns; row++)
    {
        SLC_r64_t pivot_norm = SLC_c128_abs(*pivot_ptr) / SLC_c128_abssum(pivot_ptr, rowlength);
        if ((pivot_norm > pivot_norm_threshold) && (pivot_norm > pivot_norm_max))
        {
            found = row;
            pivot_norm_max = pivot_norm;
        }
        pivot_ptr += SLC_Array_MatColumns(mat);
    }
    return found;
}

SLC_errno_t SLC_Matc128_Inv(SLC_PArray_t dst, SLC_PArray_t src, SLC_PArray_t work)
{
    // err is to detect that src is near singular.
    SLC_errno_t err = EXIT_SUCCESS;

    // check if dst and src are same size square matrices.
    assert(SLC_Array_SameSquareMatrixSize(dst, src));
    // check work size; work.rows == src.rows + 1, work.columns == 2 * src.columns.
    assert(SLC_Array_InvWorkSize(src, work));
    do {
        SLC_size_t src_rows = SLC_Array_MatRows(src);
        SLC_size_t src_columns = SLC_Array_MatColumns(src);
        SLC_size_t work_rows = SLC_Array_MatRows(work);
        SLC_size_t work_columns = SLC_Array_MatColumns(work);
        const SLC_c128_t* src_row_head = src->data._c128;
        SLC_c128_t* work_row_head = work->data._c128;
        SLC_c128_t* pivot_ptr = work_row_head;
        SLC_c128_t* work_row_center = work_row_head + src_columns;
        SLC_c128_t* swap_buffer = work_row_head + src_rows;
        SLC_c128_t* dst_row_head = dst->data._c128;

        // fill work matrix
        for (SLC_i32_t row = 0; row < src_rows; row++)
        {
            SLC_c128_copy(work_row_head, 1, src_row_head, 1, src_columns);
            SLC_c128_copy(work_row_center, 1, SLC_c128_units, 0, src_columns);
            work_row_center[row] = SLC_c128_units[1];
            src_row_head += src_columns;
            work_row_head += work_columns;
            work_row_center += work_columns;
        }

        // calculation
        for (SLC_size_t row = 0; row < src_rows; row++)
        {
            SLC_size_t remaining_work_columns = work_columns - row;
            // pivot selection
            SLC_i32_t new_pivot_row = SLC_Matc128_SelectPivot(work, src_columns, row);
            if (new_pivot_row == -1)
            { // src is singular.
                err = SLC_ESINGULAR;
                break;
            }
            else if (row != (SLC_size_t)new_pivot_row)
            {
                SLC_c128_swap(pivot_ptr, pivot_ptr + (new_pivot_row - row) * work_columns,
                    swap_buffer, remaining_work_columns);
            }

            // normalize pivot row
            SLC_c128_t scaling = SLC_c128_units[1] / (*pivot_ptr); // reciprocal of original pivot value
            SLC_c128_scaleip(pivot_ptr, &scaling, remaining_work_columns); // scaling the pivot row

            // eliminate pivot column elements except the pivot element.
            work_row_head = work->data._c128 + row;
            for (SLC_size_t row2 = 0; row2 < src_rows; row2++)
            {
                if (row == row2)
                { // skip the pivot row
                    work_row_head += work_columns;
                    continue;
                }
                scaling = -(*work_row_head);
                SLC_c128_scaleaddip(pivot_ptr, work_row_head, &scaling, remaining_work_columns);
                work_row_head += work_columns;
            }

            // move pivot to the next position
            pivot_ptr += work_columns + 1; // move to next row, next column
            swap_buffer++; // move to next column
        }
        if (err) break;

        // copy inv-mat from work to dst
        work_row_center = work->data._c128 + src_columns;
        for (SLC_size_t row = 0; row < src_rows; row++)
        {
            SLC_c128_copy(dst_row_head, 1, work_row_center, 1, src_columns);
            work_row_center += work_columns;
            dst_row_head += src_columns;
        }
    } while (0);
    return err;
}

// solve fully determined linear equation
// left * dst = right,
// left, right: known matrix
// dst: unknown solution
SLC_errno_t SLC_Matc128_Solve(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right, SLC_PArray_t work
) {
    // unit scalar element; i.e. 1.0f for float, (1.0, 0.0) for double complex,..
    const SLC_c128_t _1 = SLC_c128_units[1];
    SLC_errno_t err = EXIT_SUCCESS;
    assert(SLC_Array_MatRows(left) == SLC_Array_MatColumns(left));
    assert(SLC_Array_MatRows(left) == SLC_Array_MatRows(right));
    assert(SLC_Array_MatRows(dst) == SLC_Array_MatColumns(left));
    assert(SLC_Array_MatColumns(dst) == SLC_Array_MatColumns(right));
    assert(SLC_Array_MatRows(work) == (SLC_Array_MatRows(left) + 1));
    assert(SLC_Array_MatColumns(work) == (SLC_Array_MatColumns(left) + SLC_Array_MatColumns(right)));
    SLC_size_t left_rows = SLC_Array_MatRows(left);
    SLC_size_t right_columns = SLC_Array_MatColumns(right);
    SLC_size_t work_columns = SLC_Array_MatColumns(work);
    SLC_c128_t* work_row_head = work->data._c128;
    SLC_c128_t* work_right_head = work_row_head + left_rows; // pointer to work matrix's region holding RHS elements.
    SLC_c128_t* swap_buffer = work_row_head + work_columns * left_rows;
    SLC_c128_t* left_row_head = left->data._c128;
    SLC_c128_t* right_row_head = right->data._c128;
    SLC_c128_t* dst_row_head = dst->data._c128;
    do {
        // setup work matrix
        for (SLC_size_t row = 0; row < left_rows; row++)
        {
            SLC_c128_copy(work_row_head, 1, left_row_head, 1, left_rows);
            SLC_c128_copy(work_row_head + left_rows, 1, right_row_head, 1, right_columns);
            work_row_head += work_columns;
        }

        // upper triangulation
        work_row_head = work->data._c128;
        for (SLC_size_t row = 0; row < left_rows; row++)
        {
            SLC_size_t active_work_columns = work_columns - row;
            SLC_c128_t pivot_scale,
                *row_head_to_eliminate = work_row_head + work_columns; // pointer to the next row of pivot element
            // select pivot row
            SLC_i32_t pivot_row = SLC_Matc128_SelectPivot(work, left_rows, row);
            if (pivot_row == -1)
            { // left matrix is singular
                err = SLC_ESINGULAR;
                break;
            }
            else if (pivot_row != row)
            {
                SLC_c128_t* new_row_head = work_row_head + (pivot_row - row) * work_columns;
                SLC_c128_swap(work_row_head, new_row_head, swap_buffer, active_work_columns);
            }

            // normalize the pivot row
            pivot_scale = _1 / (*work_row_head);
            SLC_c128_scaleip(work_row_head, &pivot_scale, active_work_columns);
            // eliminate pivot column element underneath the pivot element
            for (SLC_size_t row2 = row + 1; row2 < left_rows; row2++)
            {
                pivot_scale = -(*row_head_to_eliminate);
                SLC_c128_scaleaddip(row_head_to_eliminate, work_row_head, &pivot_scale, active_work_columns);
                row_head_to_eliminate += work_columns;
            }
            work_row_head += work_columns + 1;
            swap_buffer++;
        }
        if (err) break;

        // backward substitution
        SLC_size_t row = left_rows;
        work_row_head = work->data._c128 + left_rows * work_columns + left_rows;
        work_right_head += left_rows * work_columns;
        dst_row_head += right_columns * left_rows; // move to end (just outside)
        do {            
            --row;
            work_row_head -= (work_columns + 1);
            work_right_head -= work_columns;
            dst_row_head -= right_columns;
            for (SLC_size_t dst_column = 0; dst_column < right_columns; dst_column++)
            {
                dst_row_head[dst_column] = work_right_head[dst_column];
                for (SLC_size_t work_column = 1; work_column < left_rows; work_column++)
                {
                    dst_row_head[dst_column] -= 
                        work_right_head[dst_column + work_column * right_columns] / work_row_head[work_column];
                }
            }
        } while (row != 0);
    } while (0);
    return err;
}

SLC_errno_t SLC_Matc128_EasySolve(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right)
{
    SLC_i16_t element_size = left->cont.i16[0];
    SLC_i16_t left_columns = left->cont.i16[1];
    SLC_i16_t right_columns = right->cont.i16[1];
    SLC_4i16_t work_size = { element_size, left_columns + right_columns, left->cont.i16[2] + 1, 1 };
    SLC_PArray_t work = SLC_Array_Alloca(work_size);
    SLC_Matc128_Solve(dst, left, right, work);
}

// solve overdetermined linear equation
SLC_errno_t SLC_Matc128_EasySolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right)
{
    assert(SLC_unitsizes[(SLC_size_t)SLC_c128] == SLC_Array_UnitSize(dst));
    assert(SLC_unitsizes[(SLC_size_t)SLC_c128] == SLC_Array_UnitSize(left));
    assert(SLC_unitsizes[(SLC_size_t)SLC_c128] == SLC_Array_UnitSize(right));
    SLC_4i16_t leftT_size = { left->cont.i16[0], left->cont.i16[2], left->cont.i16[1], 1 };
    SLC_4i16_t rightT_size = { right->cont.i16[0], right->cont.i16[2], right->cont.i16[1], 1 };
    SLC_4i16_t work_size = { left->cont.i16[0], left->cont.i16[1] * 2, left->cont.i16[2] + 1, 1 };
    SLC_4i16_t leftTC_left_size = { left->cont.i16[0], left->cont.i16[1], leftT_size[2], 1 };
    SLC_4i16_t leftTC_right_size = { left->cont.i16[0], right->cont.i16[1], leftT_size[2], 1 };
    SLC_PArray_t leftT = SLC_Array_Alloc(leftT_size);
    SLC_PArray_t leftTC = SLC_Array_Alloc(leftT_size);
    SLC_PArray_t leftTC_left = SLC_Array_Alloc(leftTC_left_size);
    SLC_PArray_t rightT = SLC_Array_Alloc(rightT_size);
    SLC_PArray_t leftTC_right = SLC_Array_Alloc(leftTC_right_size);
    SLC_PArray_t work = SLC_Array_Alloc(work_size);
    SLC_errno_t err = SLC_Matc128_SolveOD(dst, left, right, leftT, leftTC, leftTC_left,
        rightT, leftTC_right, work);
    free(leftT);
    free(leftTC);
    free(leftTC_left);
    free(rightT);
    free(leftTC_right);
    free(work);
    return err;
}

SLC_errno_t SLC_Matc128_SolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right,
    SLC_PArray_t leftT, SLC_PArray_t leftTC, SLC_PArray_t leftTC_left,
    SLC_PArray_t rightT, SLC_PArray_t leftTC_right,
    SLC_PArray_t work
) {
    assert(SLC_unitsizes[(SLC_size_t)SLC_c128] == SLC_Array_UnitSize(dst));
    assert(SLC_unitsizes[(SLC_size_t)SLC_c128] == SLC_Array_UnitSize(left));
    assert(SLC_unitsizes[(SLC_size_t)SLC_c128] == SLC_Array_UnitSize(right));
    assert(SLC_Array_TransposedSize2D(left, leftT));
    assert(SLC_Array_TransposedSize2D(left, leftTC));
    assert(SLC_Array_TransposedSize2D(right, rightT));
    assert(SLC_Array_ValidMatrixProduct(leftTC_left, leftTC, left));
    assert(SLC_Array_ValidMatrixProduct(leftTC_right, leftTC, right));
    SLC_Matc128_TransConj(leftTC, left);
    SLC_Matc128_Mul(leftTC_left, leftTC, left, leftT);
    SLC_Matc128_Mul(leftTC_right, leftTC, right, rightT);
    return SLC_Matc128_Solve(dst, leftTC_left, leftTC_right, work);
}

// QR decomposition
void SLC_Matc128_QRD(SLC_PArray_t dst, SLC_PArray_t src);
#pragma endregion c128_functions

// human readable print
void SLC_Matc128_Print(FILE* out, const char* header, SLC_PArray_t mat, const char* footer)
{
    fprintf(out, "%s", header);
    fprintf(out, "%d, %d\n", mat->cont.i16[1], mat->cont.i16[2]);
    const SLC_c128_t* ptr = mat->data._c128;
    for (SLC_i16_t row = 0; row < mat->cont.i16[2]; row++)
    {
        const char* delimiter = "";
        for (SLC_i16_t column = 0; column < mat->cont.i16[1]; column++)
        {
            SLC_c128_print(out, delimiter, *ptr++);
            delimiter = ",";
        }
        fprintf(out, "\n");
    }
    fprintf(out, "%s", footer);
}
