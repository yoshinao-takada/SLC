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
const fname_c = "SLC_GeometryUT.c"; // Output C source file
const fname_cin = "SLC_GeometryUT.cin"; // Input C source template file
const fname_cinfooter = "SLC_GeometryUTfoot.cin";
const curdir = path.dirname(process.argv[1]);
const typeIDs = ["r32", "r64"];
//--------------------------------------------------------------------------
// Main block
//--------------------------------------------------------------------------
CreateSourceFile(fname_cin, fname_cinfooter, fname_c);
//--------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------
function ReadAllLines(filepath)
{
    let whole = fs.readFileSync(filepath, 'utf8');
    let textInput = whole.split('\n');
    return textInput;
}

function CreateSourceFile(cin, cinfooter, c)
{
    let text = [];
    // 1) Generate file header
    const headerText = [
        "#include \"SLC/SLC_Geometry.h\"",
        "#include \"SLC/SLC_errno.h\"",
        "#include \"SLC/SLC_Log.h\"",
        "#include <assert.h>",
        ""
    ];
    headerText.forEach((e) => { text.push(e); });


    // 2) Generate definitions for each number types.
    const templateText = ReadAllLines(path.join(curdir, cin));
    const regex0 = /<NTID>/g;
    for (let index in typeIDs)
    {
        let typeID = typeIDs[index];
        templateText.forEach(function(templateLine) {
            text.push(templateLine.replace(regex0, typeID));
        });
    }

    // 3) Generate file footer
    const footerText = ReadAllLines(path.join(curdir, cinfooter));
    footerText.forEach((e) => { text.push(e); });

    // 4) Save the file
    let whole = '';
    text.forEach(function(textLine) {
        whole = whole.concat(textLine + '\n');
    });
    fs.writeFileSync(path.join(curdir, c), whole, 'utf8');
}