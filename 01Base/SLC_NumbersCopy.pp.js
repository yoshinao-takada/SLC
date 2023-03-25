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
const fname_c = "SLC_NumbersCopy.c"; // Output C source file
const fname_h = "SLC/SLC_NumbersCopy.h"; // Output C header file
const fname_cin = "SLC_NumbersCopy.cin"; // Input C source template file
const fname_hin = "SLC_NumbersCopy.hin"; // Input C header template file
const curdir = path.dirname(process.argv[1]);
const incdir = path.join(curdir, "../include");
const typeIDs = ["i8", "i16", "i32", "i64", "u8", "u16", "u32", "u64", 
                "r32", "r64", "c64", "c128", "bool"];

//--------------------------------------------------------------------------
// Main block
//--------------------------------------------------------------------------
CreateHeaderFile(fname_hin, fname_h);

CreateSourceFile(fname_cin, fname_c);

//--------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------
// read a text file as a whole and split it into lines.
function ReadAllLines(filepath)
{
    let whole = fs.readFileSync(filepath, 'utf8');
    let textInput = whole.split('\n');
    return textInput;
}

// create a header file in the project include directory.
function CreateHeaderFile(hin, h)
{
    let text = [];
    // 1) Generate file header
    const headerText = [
        "#if !defined(_SLC_NUMBERCOPY_H)",
        "#define _SLC_NUMBERCOPY_H",
        "#include \"SLC/SLC_Numbers.h\"",
    ];
    headerText.forEach((e) => {
        text.push(e);
    });

    // 2) Generate function signatures
    let templateText = ReadAllLines(path.join(curdir, hin));
    const regex = /<NTID>/g;
    typeIDs.forEach(function(typeID) {
        templateText.forEach(function(templateLine) {
            text.push(templateLine.replace(regex, typeID));
        });
    });

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

// create a C source file in the current directory.
function CreateSourceFile(cin, c)
{
    let text = [];
    // 1) Generate file header
    const headerText = [
        "#include \"SLC/SLC_NumbersCopy.h\"",
        "#include <memory.h>",
        "#define _IT\tSLC_size_t",
        ""
    ];
    headerText.forEach((e) => { text.push(e); });


    // 2) Generate definitions for each number types.
    let templateText = ReadAllLines(path.join(curdir, cin));
    const regex = /<NTID>/g;
    typeIDs.forEach(function(typeID) {
        templateText.forEach(function(templateLine) {
            text.push(templateLine.replace(regex, typeID));
        });
    });

    // 3) Generate file footer
    // do nothing

    // 4) Save the file
    let whole = '';
    text.forEach(function(textLine) {
        whole = whole.concat(textLine + '\n');
    });
    fs.writeFileSync(path.join(curdir, c), whole, 'utf8');
}