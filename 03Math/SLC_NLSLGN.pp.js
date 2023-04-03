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
const fname_c = "SLC_NLSLGN.c"; // Output C source file
const fname_h = "SLC/SLC_NLSLGN.h"; // Output C header file
const fname_cin = "SLC_NLSLGN.cin"; // Input C source template file
const fname_hin = "SLC_NLSLGN.hin"; // Input C header template file
const curdir = path.dirname(process.argv[1]);
const incdir = path.join(curdir, "../include");
const typeIDs = [ "r32", "r64", "c64", "c128" ];
const rtypeIDs = [ "r32", "r64", "r32", "r64" ];


//--------------------------------------------------------------------------
// Main block
//--------------------------------------------------------------------------
CreateHeaderFile(fname_hin, fname_h);

CreateSourceFile(fname_cin, fname_c);

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
        "#if !defined(_SLC_NLSLGN_H)",
        "#define _SLC_NLSLGN_H",
        "#include \"SLC/SLC_NLSL.h\"",
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

function CreateSourceFile(cin, c)
{
    let text = [];
    // 1) Generate file header
    const headerText = [
        "#include \"SLC/SLC_NLSLGN.h\"",
        "#include \"SLC/SLC_Array.h\"",
        "#include \"SLC/SLC_Log.h\"",
        "#include \"SLC/SLC_NumbersCopy.h\"",
        "#include \"SLC/SLC_MiniBLAS.h\"",
        "#include \"SLC/SLC_MiniLA.h\"",
        "#include <assert.h>",
        "#include <stdlib.h>",
        "#include <errno.h>",
    ];
    headerText.forEach((e) => { text.push(e); });


    // 2) Generate definitions for each number types.
    let templateText = ReadAllLines(path.join(curdir, cin));
    let regex0 = /<NTID>/g;
    let regex2 = /<RTID>/g;
    for (let typeIndex in typeIDs)
    {
        let typeID = typeIDs[typeIndex];
        let rtypeID = rtypeIDs[typeIndex];
        templateText.forEach(function(templateLine) {
            text.push(templateLine.replace(regex0, typeID).replace(regex2, rtypeID));
        });
    }

    // 3) Generate file footer
    // do nothing

    // 4) Save the file
    let whole = '';
    text.forEach(function(textLine) {
        whole = whole.concat(textLine + '\n');
    });
    fs.writeFileSync(path.join(curdir, c), whole, 'utf8');
}