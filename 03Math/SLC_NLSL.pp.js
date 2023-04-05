// What this preprocessor does
// 1) Generate file header; Usual C source files and header files have
//   Common comment like organization, author, copyright, etc. Header files
//   have pragma or define directive to prevent from duplucating to include.
// 2) Generate declaration or program statement with specialized types and identifier names.
// 3) Generate file footer; If the file header contains define directive to prevent
//   from duplicating to include.

const fs = require('fs');
const process = require('process');
const path = require('path');
const fname_h = "SLC/SLC_NLSL.h"; // Output C header file
const fname_hin = "SLC_NLSL.hin"; // Input C header template file
const curdir = path.dirname(process.argv[1]);
const incdir = path.join(curdir, "../include");
const typeIDs = [ "r32", "r64", "c64", "c128" ];
const rtypeIDs = [ "r32", "r64", "r32", "r64" ];

//--------------------------------------------------------------------------
// Main block
//--------------------------------------------------------------------------
CreateHeaderFile(fname_hin, fname_h);

//--------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------
function ReadAllLines(filepath)
{
    let whole = fs.readFileSync(filepath, 'utf8');
    let textInput = whole.split('\n');
    return textInput;
}

function CreateHeaderFile(hin, h)
{
    let text = [];
    // 1) Generate file header
    const headerText = [
        "#if !defined(_SLC_NLSL_H)",
        "#define _SLC_NLSL_H",
        "#include \"SLC/SLC_Numbers.h\"",
        "#include \"SLC/SLC_errno.h\"",
        "typedef enum {",
        "\tNLSLState_created, // created but not yet initialized",
        "\tNLSLState_initialized, // just after initialized",
        "\tNLSLState_running, // running execution",
        "\tNLSLState_iterlimit, // stopped by iteration limit",
        "\tNLSLState_converged, // stopped by convergence",
        "\tNLSLState_errabort, // stopped by error in objective or Jacobian",
        "} SLC_NLSLState_t;",
        "typedef enum {",
        "\tNLSLTraceItem_None=0,",
        "\tNLSLTraceItem_IXY=1, // iteration, x, and y",
        "\tNLSLTraceItem_IJ=2, // iteration and Jacobian",
        "\tNLSLTraceItem_INormDXNormY=4, // iteration and Norm(x), Norm(y)",
        "\tNLSLTraceItem_All=7, // All trace items are enabled.",
        "} SLC_NLSLTraceItem_t;",
        "typedef struct {",
        "\tSLC_NLSLTraceItem_t item;",
        "\tFILE* trace_out;",
        "} SLC_NLSLTrace_t, *SLC_PNLSLTrace_t;",
        "typedef const SLC_NLSLTrace_t *SLC_PCNLSLTrace_t;",
        "",
    ];
    headerText.forEach((e) => {
        text.push(e);
    });

    // 2) Generate function signatures
    let regex0 = /<NTID>/g;
    let regex2 = /<RTID>/g;
    let templateText = ReadAllLines(path.join(curdir, hin));
    for (let typeIndex in typeIDs)
    {
        let typeID = typeIDs[typeIndex];
        let rtypeID = rtypeIDs[typeIndex];
        templateText.forEach(function(templateLine) {
            text.push(templateLine.replace(regex0, typeID).replace(regex2, rtypeID));
        });
    }

    // 3) Generate file footer
    const footerText = [
        "#endif"
    ];
    footerText.forEach((e) => {
        text.push(e);
    });

    // 4) Save the file
    let whole = '';
    text.forEach(function(textLine) {
        whole = whole.concat(textLine + '\n');
    });
    fs.writeFileSync(path.join(incdir, h), whole, 'utf8');
}
