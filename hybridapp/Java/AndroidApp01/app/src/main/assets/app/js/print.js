var ProjView = "EPSG:3857"; // 表示用投影法, WGS84, 球面(半径6378137m)メルカトル図法
var WGS84 = "EPSG:4326";

$(function() {
  $('#field01', document).append(printContents[1]);
  $('#field02', document).append(printContents[3]);
  $('#field03', document).append(printContents[5]);
  $('#field04', document).append(printContents[7]);
  $('#field05', document).append(printContents[9]);
  
  // 背景図の定義
  var background = new ol.layer.Tile({
    source: new ol.source.XYZ({
      attributions: [
        new ol.Attribution({
          html: "<a href='http://maps.gsi.go.jp/development/ichiran.html' target='_blank'>地理院タイル</a>"
        })
      ],
      url: "http://cyberjapandata.gsi.go.jp/xyz/pale/{z}/{x}/{y}.png",
      projection: ProjView
    })
  });
  var layerStyle = new ol.style.Style({
    // 記号
    image: new ol.style.Icon({
      anchor: [0.5, 0.5],
      anchorXUnits: 'fraction',
      anchorYUnits: 'fraction',
      src:'app/data/marker/point.png'
    })
  });
  var centerPoint = new ol.layer.Vector({
    style: layerStyle,
    source: new ol.source.Vector({
    })
  });
  var x = parseFloat(printContents[7]);
  var y = parseFloat(printContents[9]);
  var mapLayer = [background, centerPoint];
  var mapView = new ol.View({
    projection: ProjView,
    center: ol.proj.transform([y, x], WGS84, ProjView),
    minZoom: 18,
    maxZoom: 18,
    zoom: 18
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
  var feature = new ol.Feature({
    geometry: new ol.geom.Point(
      new ol.proj.transform([y, x], WGS84, ProjView)
    )
  });
  centerPoint.getSource().addFeature(feature);
});
