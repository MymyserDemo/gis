/* ********************************************************
 * Javascriptコンポーネントロード
 ******************************************************* */
document.write('<link rel="stylesheet" type="text/css" href="app/js/jquery-ui-1.12.1/jquery-ui.min.css"/>');
document.write('<script type="text/javascript" src="app/js/jquery-ui-1.12.1/jquery-ui.min.js"></script>');

document.write('<link rel="stylesheet" type="text/css" href="app/js/w2ui-1.5.rc1/w2ui-1.5.rc1.min.css"/>');
document.write('<script type="text/javascript" src="app/js/w2ui-1.5.rc1/w2ui-1.5.rc1.min.js"></script>');

document.write('<link rel="stylesheet" type="text/css" href="app/js/v4.0.1-dist/ol.css"/>');
document.write('<script type="text/javascript" src="app/js/v4.0.1-dist/ol.js"></script>');
document.write('<script type="text/javascript" src="app/js/proj4js-2.4.0/dist/proj4.js"></script>');

/* ********************************************************
 * 画面エレメント作成
 ******************************************************* */
var div = document.createElement("div");
div.innerHTML = '\
<div      style="position: absolute;  left:   0px; top:  0px; width: 100%; height:100%;border: 1px #000000 solid;" id="mainMap"></div>\
<div      id="viewOparetion">\
  <input  style="position:absolute;left:  5px;top:  5px;width:190px; height:30px; font-size:20px;" id="searchKeywd"/>\
  <div    style="position:absolute;left:  5px;top:140px;width:200px;" id="grid"></div>\
  <button style="position:absolute;left:210px;top:  5px;width: 76px;" id="linkButton1">詳細</button>\
  <button style="position:absolute;left:290px;top:  5px;width: 95px;" id="linkButton2">単票</button>\
  <button style="position:absolute;left:390px;top:  5px;width: 95px;" id="linkButton3">リンク</button>\
  <input  style="position:absolute;left:490px;top:  5px;width:140px;font-size:x-small;" id="zahyo"></input>\
  <div    style="position:absolute;left:484px;top: 25px;width:152px;font-size:xx-small;">\
    <input type="radio" name="zahyoType" value="1" checked="checked">BL\
    <input type="radio" name="zahyoType" value="2">JGD2000\
    <input type="radio" name="zahyoType" value="3">UTM\
  </div>\
  <button style="position:absolute;left:640px;top:  5px;width: 76px;" id="optButton0">印刷</button>\
  <button style="position:absolute;left:720px;top:  5px;width: 95px;" id="optButton1">レイヤ</button>\
  <button style="position:absolute;left:820px;top:  5px;width: 76px;" id="optButton2">図名</button>\
  <button style="position:absolute;left:900px;top:  5px;width: 76px;" id="optButton3">丁目</button>\
  <button style="position:absolute;left:  5px;top: 50px;width: 55px;" id="searchButton1">前</button>\
  <button style="position:absolute;left: 65px;top: 50px;width: 80px;" id="searchButton2">検索</button>\
  <button style="position:absolute;left:150px;top: 50px;width: 55px;" id="searchButton3">後</button>\
  <div    style="position:absolute;left:  5px;top: 95px;">\
    <select id="filterMenu">\
      <option value="">選択してください</option>\
    </select>\
  </div>\
  <b>\
  <div class="optionWindow" id="optionWindow0">\
    <center>印刷</center>\
    <hr>\
    <div class="optionPanel" id="optionPanel0">\
      <div>\
        用紙サイズ<br>\
        <input type="radio" name="printSize" value="A4" checked="checked">A4<br>\
        <input type="radio" name="printSize" value="A3">A3\
      </div><br>\
      <div>\
        用紙方向<br>\
        <input type="radio" name="printDirection" value="横" checked="checked">横<br>\
        <input type="radio" name="printDirection" value="縦">縦\
      </div><br>\
      <div>\
        縮尺<br>\
        <input type="radio" name="printScale" value="1000" checked="checked">1,000<br>\
        <input type="radio" name="printScale" value="2500">2,500<br>\
        <input type="radio" name="printScale" value="5000">5,000\
      </div>\
      <br>\
      <button id="printPreview" style="width:98%">プレビュー</button>\
      <br>\
      <br>\
      プレビューの解除はESCキーを押してください。\
      <br>\
      <br>\
      印刷位置を合わせる時はプレビュー画面でドラッグしてください。\
    </div>\
  </div>\
  <div class="optionWindow" id="optionWindow1">\
    <center>レイヤ</center>\
    <hr>\
    <div class="optionPanel" id="optionPanel1">\
    </div>\
  </div>\
  <div class="optionWindow" id="optionWindow2">\
    <center>図名</center>\
    <hr>\
    <div class="optionPanel" id="optionPanel2">\
    </div>\
  </div>\
  <div class="optionWindow" id="optionWindow3">\
    <center>丁目</center>\
    <hr>\
    <div class="optionPanel" id="optionPanel3">\
    </div>\
  </div>\
  </b>\
</div>\
<div id="decoration" style="display:none">\
  <div id="printFooter" style="position: absolute;left:5mm;top:143mm;background-color:#FFFFFF;"></div>\
</div>\
';
document.body.appendChild(div);
document.body.style.cursor = 'wait';

// 地図画面表示インスタンス
var map;
// レイヤリスト
var layerList;
// 背景図
var background;
// グリッド内の座標の列位置
var gridX = 3;
var gridY = 4;
// グリッド内のリンクの列位置
var gridLink1 = 5;
var gridLink2 = 6;
// 等級の位置
var gridToukyu = 1;
// 点データリスト
var pointDataList;

var VIEW_PROJ = "EPSG:3857"; // 表示用投影法, WGS84, 球面(半径6378137m)メルカトル図法
var JGD2000_9 = "EPSG:2451"; // JGD2000, 平面直角座標系９系
var WGS84 = "EPSG:4326";
var UTM_ZONE_54N = "EPSG:32654";
var EPSG = "EPSG:";
var OPTION2_PROJ = "EPSG:4326"; // オプション２検索の座標系
var OPTION3_PROJ = "EPSG:4326"; // オプション３検索の座標系
var POINT_PROJ = "EPSG:4326";   // 点データ検索の座標系
/* ******************************************************
 * ハイブリッドインターフェース
 ***************************************************** */
// ログ出力
function mainViewLogOutput(logMessgae) {
  console.log(logMessgae);
}
// フィルターを解除する
function filterReset() {
  // 選択されているレコードを解除
  w2ui['grid'].selectNone();
  // フィルターを解除する
  w2ui['grid'].searchReset();
  // セレクトメニューを初期化する
  $('#filterMenu').selectmenu('refresh');
  $('#filterMenu').val('');
  $('#filterMenu').attr('selected', false);
  $('#filterMenu').removeAttr('selected');
  $('#filterMenu').prop('selected', false);
  $('#filterMenu').prop('selectedIndex', 0);
}
// Hybrid側から呼ばれるアプリ側のデータリストタイトル行追加
function mainViewDataListAddHeader(data) {
  mainViewLogOutput(mainViewDataListAddHeader.name);
  // JSONに変換
  var obj = JSON.parse(data);
  var inum = Object.keys(obj.data).length;
  w2ui['grid'].addColumn({field:obj.data[0].field, caption:obj.data[0].caption, size: '50px' });
  w2ui['grid'].addColumn({field:obj.data[1].field, caption:obj.data[1].caption, size: '50px' });
  for(var i =2; i < inum; i++) {
    // カラムの追加
    w2ui['grid'].addColumn({field:obj.data[i].field, caption:obj.data[i].caption, size: '100px' });
  }
}
// Hybrid側から呼ばれるアプリ側のデータリスト行データ追加
function mainViewDataListAddData(data) {
  mainViewLogOutput(mainViewDataListAddData.name);
  // JSONに変換
  pointDataList = JSON.parse(data);
  // 一覧表に一括登録
  w2ui['grid'].add(pointDataList);
  // フィルター一覧登録
  var inum = Object.keys(pointDataList).length;
  var filter = [pointDataList[0].区分];
  var fCount = 0;
  for(var i = 0; i < inum; i++) {
    var jnum = filter.length;
    var j = 0;
    for(; j < jnum; j++) {
      if(pointDataList[i].区分 == filter[j]) {
        break;
      }
    }
    if(j != jnum) {
      continue;
    }
    filter[fCount] = pointDataList[i].区分
    $('#filterMenu').append($('<option>').html(filter[fCount]).val(fCount));
    fCount = fCount + 1;
  }
}

// Hybrid側から呼ばれるアプリ側のオプション1表示
var option1DataList;
function mainViewOption1(data) {
  mainViewLogOutput(mainViewOption1.name);
  // JSONに変換
  option1DataList = JSON.parse(data);
  // レイヤ数
  var num = Object.keys(option1DataList).length;
  layerList = new Array(num);
  var i;
  for(i = 0; i < num; i++) {
    $('#optionPanel1').append("<label>" + option1DataList[i].layerName + " </label>");
    var element = $("<input type='checkbox' id='option" + i + "' class='optionlist' title='" + i + "'>");
    // 初期表示設定
    element.attr("checked",option1DataList[i].initial == "TRUE");
    // エレメント追加
    $('#optionPanel1').append(element);
    $('#optionPanel1').append("<br>");
    // 変更した時の処理を設定
    $(element).change(function(){layerList[this.title].setVisible(this.checked);});
  }
  for(i = 1; i < num; i++) {
    // レイヤスタイル設定
    var layerStyle = new ol.style.Style({
      // ラインスタイル
      stroke: new ol.style.Stroke({
        color: option1DataList[i].lineColor,
        width: option1DataList[i].lineWidth
      }),
      // 記号スタイル
      image: new ol.style.Icon({
        anchor: [0.5, 0.5],
        anchorXUnits: 'fraction',
        anchorYUnits: 'fraction',
        src:option1DataList[i].marker
      })
    });
    // レイヤー作成
    layerList[i] = new ol.layer.Vector({
      style: layerStyle,
      source: new ol.source.Vector({
      }),
      minResolution: option1DataList[i].minResolution,
      maxResolution: option1DataList[i].maxResolution,
      opacity: option1DataList[i].opacity,
      zIndex: i
    });
    layerList[i].setVisible(option1DataList[i].initial == "TRUE");
    // 地図にレイヤを追加
    map.addLayer(layerList[i]);
  }
  // 背景をレイヤ情報の先頭に設定する
  layerList[0] = background;
  // 点を描画
  if(pointDataList != undefined) {
    var jnum = Object.keys(pointDataList).length;
    for(var j = 0; j < jnum; j++) {
      for(var k = 0; k < num; k++) {
        if(option1DataList[k].layerName != pointDataList[j].等級) {
          continue;
        }
        drawPoint(
          k,
          parseFloat(pointDataList[j].x),
          parseFloat(pointDataList[j].y),
          parseFloat(pointDataList[j].rotation),
          option1DataList[k].marker,
          pointDataList[j].点番号,
          j,
          EPSG + option1DataList[k].epsg
        );
      }
    }
  }
  document.body.style.cursor = 'auto';
}

// 点の表示スタイル設定
function createPointStyle(feature, layerNo) {
  return new ol.style.Style({
    image: new ol.style.Icon({
      anchor: [0.5, 0.5],
      anchorXUnits: 'fraction',
      anchorYUnits: 'fraction',
      src: feature.get("markerImage")
    }),
    text : new ol.style.Text({
      fill: new ol.style.Fill({color:option1DataList[layerNo].textColor}),
      scale: option1DataList[layerNo].textSize,
      textAlign: option1DataList[layerNo].textAlign,
      textBaseline: option1DataList[layerNo].textBaseline,
      offsetX: option1DataList[layerNo].offsetX,
      offsetY: option1DataList[layerNo].offsetY,
      font: option1DataList[layerNo].font,
      rotation: feature.get("rotation")/180*3.141592,
      text: feature.get("name")
    })
  });
}

// マーカー描画
function drawPoint(layerNo, x, y, rotation, icon, label, id, proj) {
  var feature = new ol.Feature({
      geometry: new ol.geom.Point(
        new ol.proj.transform([y, x], proj, VIEW_PROJ)
      ),
      name: label,
      markerImage: icon,
      rotation: rotation
  });
  feature.setId(id);
  var pointStyle = createPointStyle(feature, layerNo);
  feature.setStyle(pointStyle);
  layerList[layerNo].getSource().addFeature(feature);
}

var selectedPoint = undefined;

// マーカー描画
function selectedMarker(layerNo, x, y, icon, proj) {
  var feature = new ol.Feature({
      geometry: new ol.geom.Point(
        new ol.proj.transform([y, x], proj, VIEW_PROJ)
      ),
      markerImage: icon
  });
  var pointStyle = createPointStyle(feature, layerNo);
  feature.setStyle(pointStyle);
  layerList[layerNo].getSource().addFeature(feature);
  return feature;
}

// ライン描画
function drawLine(layerNo, x1, y1, x2, y2, lineColor, lineWidth, proj) {
  // 線分点列
  var coords = [[y1, x1], [y2,x2]];
  var lineString = new ol.geom.LineString(coords);
  // 投影法設定
  lineString.transform(proj, VIEW_PROJ);
  // フィーチャー作成
  var linestring_feature = new ol.Feature({ geometry: lineString });
  if (!(lineColor === undefined || lineWidth === undefined)) {
    // ラインスタイル
    var lineStyle = new ol.style.Style({
      stroke: new ol.style.Stroke({
        color: lineColor,
        width: lineWidth
      }),
    });
    linestring_feature.setStyle(lineStyle);
  }
  // 線分描画
  layerList[layerNo].getSource().addFeature(linestring_feature);
}

// Hybrid側から呼ばれるアプリ側のオプション2表示
var option2DataList;
function mainViewOption2(data) {
  // JSONに変換
  option2DataList = JSON.parse(data);
  var num = Object.keys(option2DataList).length;
  // オプションをクリックした時の処理
  onClickFunction = function(){
    var x = parseFloat(option2DataList[this.title].x);
    var y = parseFloat(option2DataList[this.title].y);
    // アニメーション効果を表示しながら地図表示位置移動
    map.getView().animate({
      center: ol.proj.transform([y, x], OPTION2_PROJ, VIEW_PROJ),
      duration: 1000
    });
  };
  for(var i = 0; i < num; i++) {
    var element = $("<div id='option2" + i + "' title='" + i +  "'>" + option2DataList[i].図名 + "</div>");
    $('#optionPanel2').append(element);
    // クリックされた時の関数を設定
    $(element).click(onClickFunction);
  }
}

// Hybrid側から呼ばれるアプリ側のオプション3表示
var option3DataList;
function mainViewOption3(data) {
  // JSONに変換
  option3DataList = JSON.parse(data);
  var num = Object.keys(option3DataList).length;
  // オプションをクリックした時の処理
  onClickFunction = function(){
    var x = parseFloat(option3DataList[this.title].x);
    var y = parseFloat(option3DataList[this.title].y);
    // アニメーション効果を表示しながら地図表示位置移動
    map.getView().animate({
      center: ol.proj.transform([y, x], OPTION3_PROJ, VIEW_PROJ),
      duration: 1000
    });
  };
  for(var i = 0; i < num; i++) {
    var element = $("<div id='option2" + i + "' title='" + i +  "'>" + option3DataList[i].町丁目 + "</div>");
    $('#optionPanel3').append(element);
    // クリックされた時の関数を設定
    $(element).click(onClickFunction);
  }
}

// Hybrid側から呼ばれるアプリ側のポイント表示
function mainViewPutPoint(data, layerNo) {
  mainViewLogOutput(mainViewPutPoint.name);
  // JSONに変換
  var obj = JSON.parse(data);
  var num = Object.keys(obj.data).length;
  for(var i = 0; i < num; i++) {
    drawPoint(
      layerNo-1,
      parseFloat(obj.data[i].x),
      parseFloat(obj.data[i].y),
      parseFloat(obj.data[i].rotation),
      "app/data/marker/marker.png",
      obj.data[i].name,
      i,
      EPSG + option1DataList[layerNo-1].epsg
    );
  }
}

// Hybrid側から呼ばれるアプリ側のライン表示
function mainViewPutLine(data, layerNo) {
  mainViewLogOutput(mainViewPutLine.name);
  // JSONに変換
  var obj = JSON.parse(data);
  var num = Object.keys(obj.data).length;
  for(var i = 0; i < num; i++) {
    drawLine(
      obj.data[i].layerNo,
      obj.data[i].x1,
      obj.data[i].y1,
      obj.data[i].x2,
      obj.data[i].y2,
      obj.data[i].lineColor,
      obj.data[i].lineWidth,
      EPSG + option1DataList[layerNo-1].epsg
    );
  }
}

// Hybrid側から呼ばれるアプリ側のGeoJson表示
function putGeoJsonComplete(data, layerNo) {
  // データロード完了後
  // GeoJSONオブジェクト作成
  var geojsonObject = JSON.parse(data);
  // フィーチャーに変換、この時featureProjectionは表示用の投影を指定する
  var vectorSource = new ol.source.Vector({
    features: (new ol.format.GeoJSON()).readFeatures(geojsonObject, {
      // データの投影法
      dataProjection : EPSG + option1DataList[layerNo-1].epsg,
      // 表示の投影法
      featureProjection: VIEW_PROJ
    })
  });
  // レイヤにGeoJSONフィーチャーをソースとして設定する
  layerList[layerNo-1].setSource(vectorSource);
}

// Hybrid側から呼ばれるアプリ側のGeoJson表示
function mainViewPutGeoJson(fileName, layerNo) {
  mainViewLogOutput(mainViewPutGeoJson.name);
  commonFileLoad(fileName, null, putGeoJsonComplete, layerNo);
}

// Windowリサイズ時処理
function windowResize() {
  var offset = $('#grid').offset();
  var h = $(window).height() - offset.top -5;
  $('#grid').height(h);
  optionWindowResize('0');
  optionWindowResize('1');
  optionWindowResize('2');
  optionWindowResize('3');
}

// オプションWindowリサイズ
function optionWindowResize(optionNo) {
  var offset =$('#optionPanel' + optionNo).offset();
  var h = $(window).height() - offset.top -5;
  $('#optionPanel' + optionNo).height(h);
  offset = $('#optionWindow' + optionNo).offset();
  h = $(window).height() - offset.top -5;
  $('#optionWindow' + optionNo).height(h);
}

// 選択点にマーカー設置
function pointSelected(id) {
  // 選択点にマーカーを置く
  var x = parseFloat(pointDataList[id].x);
  var y = parseFloat(pointDataList[id].y);
  var drawLayer = option1DataList.length -1;
  var epsg = EPSG + option1DataList[drawLayer-1].epsg;
  // 新規にマーカーを置く
  if(selectedPoint === undefined) {
    selectedPoint = selectedMarker(
      drawLayer, x, y,
      option1DataList[drawLayer].marker,
      epsg
    );
  }
  // 既にあるマーカーの位置を選択点に移動する
  else {
    selectedPoint.set('geometry',
      new ol.geom.Point(
        new ol.proj.transform([y, x], epsg, VIEW_PROJ)
      )
    );
  }
}

/* ********************************************************
 * View側の処理
 ******************************************************* */
$(function() {
  /* ******************************************************
   * 画面初期処理
   ***************************************************** */
  // ボタン設定
  $('button').button();
  // ポイントリスト設定
  $('#optionlist').checkboxradio();
  // ポイントリストフィルター設定
  $('#filterMenu').selectmenu({width:$('#grid').width()});
  // ポイントリスト
  $('#grid').w2grid({
    name:'grid'
  });
  /* ******************************************************
   * イベント処理定義
   ***************************************************** */
  // 画面ロード完了時イベント
  $(document).ready(function(){
    windowResize();
  });
  // Windowリサイズイベント
  $(window).on('load resize', function() {
    windowResize();
  });
  /* ******************************************************
   * 地図
   ***************************************************** */
  // 平面直角座標系９系の定義
  proj4.defs[JGD2000_9] =    proj4.Proj('PROJCS["JGD2000 / Japan Plane Rectangular CS IX",GEOGCS["JGD2000",DATUM["Japanese_Geodetic_Datum_2000",SPHEROID["GRS 1980",6378137,298.257222101,AUTHORITY["EPSG","7019"]],TOWGS84[0,0,0,0,0,0,0],AUTHORITY["EPSG","6612"]],PRIMEM["Greenwich",0,AUTHORITY["EPSG","8901"]],UNIT["degree",0.0174532925199433,AUTHORITY["EPSG","9122"]],AUTHORITY["EPSG","4612"]],PROJECTION["Transverse_Mercator"],PARAMETER["latitude_of_origin",36],PARAMETER["central_meridian",139.8333333333333],PARAMETER["scale_factor",0.9999],PARAMETER["false_easting",0],PARAMETER["false_northing",0],UNIT["metre",1,AUTHORITY["EPSG","9001"]],AUTHORITY["EPSG","2451"]]');
  proj4.defs[UTM_ZONE_54N] = proj4.Proj('+proj=utm +zone=54 +ellps=WGS84 +datum=WGS84 +units=m +no_defs');
  // 背景図の定義
  background = new ol.layer.Tile({
    source: new ol.source.XYZ({
      attributions: [
        new ol.Attribution({
          html: "<a href='http://maps.gsi.go.jp/development/ichiran.html' target='_blank'>地理院タイル</a>"
        })
      ],
      url: "http://cyberjapandata.gsi.go.jp/xyz/pale/{z}/{x}/{y}.png",
      projection: VIEW_PROJ
    }),
    opacity: 1.0,
    zIndex: 0
  });
  var mapLayer = [background];
  var mapView = new ol.View({
    projection: VIEW_PROJ,
    center: ol.proj.transform([-7550, -34015], "EPSG:2451", VIEW_PROJ),
    minZoom: 5,
    maxZoom: 20,
    zoom: 14
  });
  var mapRenderer = ['canvas', 'dom'];
  // 地図初期設定
  map = new ol.Map({
    target  : "mainMap",
    renderer: mapRenderer,
    layers  : mapLayer,
    view    : mapView,
    controls: []
  });
  $(map.on('click', function(e) {
    // クリックした位置の座標を表示する
    var x;
    var y;
    var clickPosition;
    // 経緯度
    if($('input[name=zahyoType]:checked').val() === "1") {
      clickPosition = ol.proj.transform(e.coordinate, VIEW_PROJ, WGS84);
      x = String(clickPosition[0]);
      if(x.length > 11) {
        x = x.substr(0, 11);
      }
      y = String(clickPosition[1]);
      if(y.length > 10) {
        y = y.substr(0, 10);
      }
      $("#zahyo").val(x + "," + y);
    }
    // 平面直角座標系９系
    else if($('input[name=zahyoType]:checked').val() === "2") {
      clickPosition = ol.proj.transform(e.coordinate, VIEW_PROJ, JGD2000_9);
      x = String(Math.round(clickPosition[0]*1000)/1000);
      y = String(Math.round(clickPosition[1]*1000)/1000);
      $("#zahyo").val(y + "," + x);
    }
    else {
      clickPosition = ol.proj.transform(e.coordinate, VIEW_PROJ, UTM_ZONE_54N);
      x = String(Math.round(clickPosition[0]));
      x = x.substring(1,x.length-1);
      y = String(Math.round(clickPosition[1]));
      y = y.substring(2,y.length-1);
      $("#zahyo").val("54S-UE-" + x + "-" + y);
    }
  }));
  // 地図からポイントリストを検索
  $(map.getViewport()).on("click", function(e) {
    map.forEachFeatureAtPixel(map.getEventPixel(e), function (feature, layer) {
      var layerNo = layer.getZIndex();
      // 点レイヤー以外は何もしない
      if(option1DataList[layerNo].layerType != "CSVPOINT") {
        return;
      }
      if(map.getView().getZoom() < 16) {
        return;
      }
      document.body.style.cursor = 'wait';
      var id = feature.getId();
      if(id === undefined) {
        return;
      }
      // フィルターを解除する
      filterReset();
      // フィルターを解除する
      filterReset();
      // 選択されているレコードを解除
      w2ui['grid'].selectNone();
      // フィルターを解除する
      w2ui['grid'].searchReset();
      // ポイントリストの当該点を選択状態にする
      w2ui['grid'].scrollIntoView(id);
      w2ui['grid'].select(id);
      // 選択点にマーカー設置
      pointSelected(id);
      document.body.style.cursor = 'auto';
    });
  });
  /* ******************************************************
   * リンクボタン
   ***************************************************** */
  // 詳細
  $("#linkButton1").click(function() {
    var recid = w2ui['grid'].getSelection();
    if(recid[0] === undefined) {
      return;
    }
    // 検索実行
    var detail = Pointer_stringify(Module._bridginggetLoadDataDetail([allocate(intArrayFromString("PointList"), 'i8', ALLOC_STACK)], recid[0]));
    // 印刷用ページを開く
    var printWin = window.open("printdetail.html?" + detail);
  });
  // 単票
  $("#linkButton2").click(function() {
    var recid = w2ui['grid'].getSelection();
    if(recid[0] === undefined) {
      return;
    }
    // 検索実行
    var detail = Pointer_stringify(Module._bridginggetLoadDataDetail([allocate(intArrayFromString("PointList"), 'i8', ALLOC_STACK)], recid[0]));
    // 印刷用ページを開く
    var printWin = window.open("print.html?" + encodeURI(detail));
  });
  // リンク
  $("#linkButton3").click(function() {
    var recid = w2ui['grid'].getSelection();
    if(recid[0] === undefined) {
      return;
    }
    var sel = w2ui['grid'].getSelection();
    var link = w2ui['grid'].getCellValue(sel[0], gridLink1);
    var printWin = window.open(link);
  });
  /* ******************************************************
   * オプションボタン
   ***************************************************** */
  // オプション0クリック処理
  $("#optButton0").click(function(){
    if ($('#optionWindow0').is(':visible')) {
      $('#optionWindow0').hide();
    } else {
      $('#optionWindow0').show();
      $('#optionWindow1').hide();
      $('#optionWindow2').hide();
      $('#optionWindow3').hide();
    }
    optionWindowResize('0');
  });
  // オプション1クリック処理
  $("#optButton1").click(function(){
    if ($('#optionWindow1').is(':visible')) {
      $('#optionWindow1').hide();
    } else {
      $('#optionWindow0').hide();
      $('#optionWindow1').show();
      $('#optionWindow2').hide();
      $('#optionWindow3').hide();
    }
    optionWindowResize('1');
  });
  // オプション2クリック処理
  $("#optButton2").click(function(){
    if ($('#optionWindow2').is(':visible')) {
      $('#optionWindow2').hide();
    } else {
      $('#optionWindow0').hide();
      $('#optionWindow1').hide();
      $('#optionWindow2').show();
      $('#optionWindow3').hide();
    }
    optionWindowResize('2');
  });
  // オプション3クリック処理
  $("#optButton3").click(function(){
    if ($('#optionWindow3').is(':visible')) {
      $('#optionWindow3').hide();
    } else {
      $('#optionWindow0').hide();
      $('#optionWindow1').hide();
      $('#optionWindow2').hide();
      $('#optionWindow3').show();
    }
    optionWindowResize('3');
  });
  /* ******************************************************
   * 検索ボタン
   ***************************************************** */
  // 先頭から検索
  function serachLoadDataListRecord(position, direction) {
    mainViewLogOutput(serachLoadDataListRecord.name);
    var key = $("#searchKeywd").val();
    if(key == "") {
      return;
    }
    // フィルター解除
    filterReset();
    // 検索実行
    var result = Module._bridgingSerachLoadDataListRecord(
      [allocate(intArrayFromString("PointList"), 'i8', ALLOC_STACK)],
      [allocate(intArrayFromString(key), 'i8', ALLOC_STACK)],
      parseInt(position),
      direction,
      2
    );
    // 検索結果なし
    if(result < 0) {
      return;
    }
    // レコードを選択と同時にクリックイベント発生
    w2ui['grid'].scrollIntoView(result);
    w2ui['grid'].click(result, { metaKey: true });
    // 選択点にマーカー設置
    pointSelected(result);
  }
  // 前ボタンクリックイベント
  $("#searchButton1").click(function() {
    var recid = w2ui['grid'].getSelection();
    if(recid[0] === undefined) {
      return;
    }
    // フィルター解除
    filterReset();
    serachLoadDataListRecord(recid[0]-1, false);
  });
  // 検索ボタンクリックイベント
  $("#searchButton2").click(function() {
    // フィルター解除
    filterReset();
    serachLoadDataListRecord(0, true);
  });
  // 入力フィールドキーボードイベント
  $("#searchKeywd").on("click keydown", function(e) {
    if(e.keyCode === 13) {
      // フィルター解除
      filterReset();
      serachLoadDataListRecord(0, true);
    }
  });
  // 後ボタンクリックイベント
  $("#searchButton3").click(function() {
    var recid = w2ui['grid'].getSelection();
    if(recid[0] === undefined) {
      return;
    }
    // フィルター解除
    filterReset();
    serachLoadDataListRecord(recid[0]+1, true);
  });
  // フィルター実行
  $("#filterMenu").selectmenu({
    change: function( event, ui ) {
      // 選択されているレコードを解除
      w2ui['grid'].selectNone();
      var str = $(this).val();
      if(str == "") {
        // フィルターを解除する
        w2ui['grid'].searchReset();
      }
      else {
        // フィルターを実行する
        w2ui['grid'].search([{ field: "区分",
          value:$("#filterMenu option:selected").text(),
          operator: "is"
        }]);
      }
    }
  });
  /* ******************************************************
   * ポイントリスト
   ***************************************************** */
  // ポイントリストクリック
  w2ui['grid'].on('click', function(event) {
    var grid = this;
    event.onComplete = function () {
      // クリックされた行
      var result = grid.getSelection();
      var x = parseFloat(grid.getCellValue(result[0], gridX));
      var y = parseFloat(grid.getCellValue(result[0], gridY));
      if(isNaN(x) || isNaN(y)) {
        return;
      }
      // アニメーション効果を表示しながら地図表示位置移動
      map.getView().animate({
        center: ol.proj.transform([y, x], POINT_PROJ, VIEW_PROJ),
        duration: 1000,
        zoom: 18
      });
      // 選択点にマーカー設置
      pointSelected(result[0]);
    }
  });
  /* ******************************************************
   * 地図印刷
   ***************************************************** */
  // 印刷プレビューボタン
  $("#printPreview").click(function() {
    $("#decoration").show();
    $("#viewOparetion").hide();
    // 用紙サイズ設定
    if($('input[name=printSize]:checked').val() === "A4") {
      // 用紙方向設定
      if($('input[name=printDirection]:checked').val() === "横") {
        $('#mainMap').height("168mm").width("255mm");
        $("#printFooter").css({top:"163mm"});
      }
      // 縦
      else {
        $('#mainMap').height("255mm").width("168mm");
        $("#printFooter").css({top:"250mm"});
      }
    }
    // A3
    else {
      // 用紙方向設定
      if($('input[name=printDirection]:checked').val() === "横") {
        $('#mainMap').height("255mm").width("378mm");
        $("#printFooter").css({top:"250mm"});
      }
      // 縦
      else {
        $('#mainMap').height("378mm").width("255mm");
        $("#printFooter").css({top:"373mm"});
      }
    }
    map.updateSize();
    // 縮尺設定
    if($('input[name=printScale]:checked').val() === "1000") {
      map.getView().setZoom(18);
    }
    else if($('input[name=printScale]:checked').val() === "2500") {
      map.getView().setZoom(17);
    }
    // 5000
    else {
      map.getView().setZoom(16);
    }
  });
  // 印刷プレビュー解除
  $(window).keyup(function(e) {
    // エスケープキー
    if(e.keyCode != 27) {
      return;
    }
    if ($("#viewOparetion").is(":hidden")) {
      event.stopImmediatePropagation();
      $('#mainMap').height("100%").width("100%");
      map.updateSize();
      $("#viewOparetion").show();
      $("#decoration").hide();
    }
  });
});
