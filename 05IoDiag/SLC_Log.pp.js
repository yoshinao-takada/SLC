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
const fname_h = "SLC/SLC_Log.h"; // Output C header file
const fname_hin = "SLC_Log.hin"; // Input C header template file
const fname_head_hin = "SLC_LogHead.hin"; // header part of C header file
const curdir = path.dirname(process.argv[1]);
const incdir = path.join(curdir, "../include");
const typeIDs = [ "r32", "r64", "c64", "c128" ];

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
    let headerText = ReadAllLines(fname_head_hin);
    headerText.forEach((e) => {
        text.push(e);
    });

    // 2) Generate function signatures
    let regex0 = /<NTID>/g;
    let templateText = ReadAllLines(path.join(curdir, hin));
    typeIDs.forEach(function(typeID) {
        templateText.forEach(function(templateLine) {
            text.push(templateLine.replace(regex0, typeID));
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
