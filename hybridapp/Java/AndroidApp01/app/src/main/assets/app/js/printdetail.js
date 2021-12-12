// ログ出力
function printLogOutput(logMessgae) {
  console.log(logMessgae);
}

$(function() {
  $("#detail").append("<tr><td style='width:40px'><div class='TextCenter'>No</div></td><td style='width:150px'><div class='TextLeft'>項目名</div></td><td><div class='TextLeft'>内容</div></td></tr>");
  var val = decodeURI(location.search.substr(1)).split(",");
  var num = val.length / 2;
  for(var i = 0; i < num; i++) {
    printLogOutput(val[i*2] + ":" + val[i*2+1]);
    $("#detail").append("<tr><td><div class='TextRight'>" + (i+1) + "</div></td><td><div class='TextLeft'>" + val[i*2] + "</div></td><td><div class='TextLeft'>" + val[i*2+1] + "</div></td></tr>");
  }
});
