
const nrows = 12; const ncols = 12

 let table = ""



 for (let r = 0; r < nrows; r++) {

 table += '<tr>'

 for (let c = 0; c < ncols; c++) {

 table += "<td>" + (r+1)*(c+1)+ "</td>"

 }

 table += "</tr>"

 }



 document.write("<table>" + table + "</table>")

