var NAVTREE =
[
  [ "libRacv", "index.html", [
    [ "Class List", "annotated.html", [
      [ "racv::DataSaviour", "classracv_1_1DataSaviour.html", null ],
      [ "racv::DebugPipe", "classracv_1_1DebugPipe.html", null ],
      [ "racv::Detector", "classracv_1_1Detector.html", null ],
      [ "racv::DrawRectangles", "classracv_1_1DrawRectangles.html", null ],
      [ "racv::ExtractRectangles", "classracv_1_1ExtractRectangles.html", null ],
      [ "racv::Gray", "classracv_1_1Gray.html", null ],
      [ "racv::Pipe", "classracv_1_1Pipe.html", null ],
      [ "racv::Pipe::PipeMsg", "structracv_1_1Pipe_1_1PipeMsg.html", null ],
      [ "racv::Reservoir", "classracv_1_1Reservoir.html", null ],
      [ "racv::ShowFrames", "classracv_1_1ShowFrames.html", null ],
      [ "racv::SwitchPipe", "classracv_1_1SwitchPipe.html", null ],
      [ "racv::Track", "classracv_1_1Track.html", null ],
      [ "racv::WriteFrames", "classracv_1_1WriteFrames.html", null ],
      [ "racv::WriteVideo", "classracv_1_1WriteVideo.html", null ]
    ] ],
    [ "Class Index", "classes.html", null ],
    [ "Class Hierarchy", "hierarchy.html", [
      [ "racv::Pipe", "classracv_1_1Pipe.html", [
        [ "racv::DataSaviour", "classracv_1_1DataSaviour.html", null ],
        [ "racv::DebugPipe", "classracv_1_1DebugPipe.html", null ],
        [ "racv::Detector", "classracv_1_1Detector.html", null ],
        [ "racv::DrawRectangles", "classracv_1_1DrawRectangles.html", null ],
        [ "racv::ExtractRectangles", "classracv_1_1ExtractRectangles.html", null ],
        [ "racv::Gray", "classracv_1_1Gray.html", null ],
        [ "racv::ShowFrames", "classracv_1_1ShowFrames.html", null ],
        [ "racv::SwitchPipe", "classracv_1_1SwitchPipe.html", null ],
        [ "racv::Track", "classracv_1_1Track.html", null ],
        [ "racv::WriteFrames", "classracv_1_1WriteFrames.html", null ],
        [ "racv::WriteVideo", "classracv_1_1WriteVideo.html", null ]
      ] ],
      [ "racv::Pipe::PipeMsg", "structracv_1_1Pipe_1_1PipeMsg.html", null ],
      [ "racv::Reservoir", "classracv_1_1Reservoir.html", null ]
    ] ],
    [ "Class Members", "functions.html", null ],
    [ "Namespace List", "namespaces.html", [
      [ "racv", "namespaceracv.html", null ]
    ] ],
    [ "Namespace Members", "namespacemembers.html", null ],
    [ "File List", "files.html", [
      [ "include/libRacv/libRacv.hpp", "libRacv_8hpp.html", null ],
      [ "include/libRacv/pipes/pipes.hpp", "pipes_8hpp.html", null ],
      [ "include/libRacv/pipes/core/Pipe.hpp", "Pipe_8hpp.html", null ],
      [ "include/libRacv/pipes/core/Reservoir.hpp", "Reservoir_8hpp.html", null ],
      [ "include/libRacv/pipes/misc/DataSaviour.hpp", "DataSaviour_8hpp.html", null ],
      [ "include/libRacv/pipes/misc/DebugPipe.hpp", "DebugPipe_8hpp.html", null ],
      [ "include/libRacv/pipes/misc/Detector.hpp", "Detector_8hpp.html", null ],
      [ "include/libRacv/pipes/misc/DrawRectangles.hpp", "DrawRectangles_8hpp.html", null ],
      [ "include/libRacv/pipes/misc/ExtractRectangles.hpp", "ExtractRectangles_8hpp.html", null ],
      [ "include/libRacv/pipes/misc/Gray.hpp", "Gray_8hpp.html", null ],
      [ "include/libRacv/pipes/misc/ShowFrames.hpp", "ShowFrames_8hpp.html", null ],
      [ "include/libRacv/pipes/misc/SwitchPipe.hpp", "SwitchPipe_8hpp.html", null ],
      [ "include/libRacv/pipes/misc/Track.hpp", "Track_8hpp.html", null ],
      [ "include/libRacv/pipes/misc/WriteFrames.hpp", "WriteFrames_8hpp.html", null ],
      [ "include/libRacv/pipes/misc/WriteVideo.hpp", "WriteVideo_8hpp.html", null ],
      [ "include/libRacv/tools/color.hpp", "color_8hpp.html", null ],
      [ "include/libRacv/tools/detection.hpp", "detection_8hpp.html", null ],
      [ "include/libRacv/tools/matrix.hpp", "matrix_8hpp.html", null ],
      [ "include/libRacv/tools/points.hpp", "points_8hpp.html", null ],
      [ "include/libRacv/tools/rectangle.hpp", "rectangle_8hpp.html", null ],
      [ "include/libRacv/tools/video.hpp", "video_8hpp.html", null ],
      [ "include/libRacv/tools/colorNormalization/colorNormalization.hpp", "colorNormalization_8hpp.html", null ],
      [ "include/libRacv/tools/colorNormalization/greyworld.hpp", "greyworld_8hpp.html", null ],
      [ "include/libRacv/tools/drawing/drawing.hpp", "drawing_8hpp.html", null ],
      [ "include/libRacv/tools/drawing/ellipse.hpp", "ellipse_8hpp.html", null ]
    ] ],
    [ "File Members", "globals.html", null ]
  ] ]
];

function createIndent(o,domNode,node,level)
{
  if (node.parentNode && node.parentNode.parentNode)
  {
    createIndent(o,domNode,node.parentNode,level+1);
  }
  var imgNode = document.createElement("img");
  if (level==0 && node.childrenData)
  {
    node.plus_img = imgNode;
    node.expandToggle = document.createElement("a");
    node.expandToggle.href = "javascript:void(0)";
    node.expandToggle.onclick = function() 
    {
      if (node.expanded) 
      {
        $(node.getChildrenUL()).slideUp("fast");
        if (node.isLast)
        {
          node.plus_img.src = node.relpath+"ftv2plastnode.png";
        }
        else
        {
          node.plus_img.src = node.relpath+"ftv2pnode.png";
        }
        node.expanded = false;
      } 
      else 
      {
        expandNode(o, node, false);
      }
    }
    node.expandToggle.appendChild(imgNode);
    domNode.appendChild(node.expandToggle);
  }
  else
  {
    domNode.appendChild(imgNode);
  }
  if (level==0)
  {
    if (node.isLast)
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2plastnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2lastnode.png";
        domNode.appendChild(imgNode);
      }
    }
    else
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2pnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2node.png";
        domNode.appendChild(imgNode);
      }
    }
  }
  else
  {
    if (node.isLast)
    {
      imgNode.src = node.relpath+"ftv2blank.png";
    }
    else
    {
      imgNode.src = node.relpath+"ftv2vertline.png";
    }
  }
  imgNode.border = "0";
}

function newNode(o, po, text, link, childrenData, lastNode)
{
  var node = new Object();
  node.children = Array();
  node.childrenData = childrenData;
  node.depth = po.depth + 1;
  node.relpath = po.relpath;
  node.isLast = lastNode;

  node.li = document.createElement("li");
  po.getChildrenUL().appendChild(node.li);
  node.parentNode = po;

  node.itemDiv = document.createElement("div");
  node.itemDiv.className = "item";

  node.labelSpan = document.createElement("span");
  node.labelSpan.className = "label";

  createIndent(o,node.itemDiv,node,0);
  node.itemDiv.appendChild(node.labelSpan);
  node.li.appendChild(node.itemDiv);

  var a = document.createElement("a");
  node.labelSpan.appendChild(a);
  node.label = document.createTextNode(text);
  a.appendChild(node.label);
  if (link) 
  {
    a.href = node.relpath+link;
  } 
  else 
  {
    if (childrenData != null) 
    {
      a.className = "nolink";
      a.href = "javascript:void(0)";
      a.onclick = node.expandToggle.onclick;
      node.expanded = false;
    }
  }

  node.childrenUL = null;
  node.getChildrenUL = function() 
  {
    if (!node.childrenUL) 
    {
      node.childrenUL = document.createElement("ul");
      node.childrenUL.className = "children_ul";
      node.childrenUL.style.display = "none";
      node.li.appendChild(node.childrenUL);
    }
    return node.childrenUL;
  };

  return node;
}

function showRoot()
{
  var headerHeight = $("#top").height();
  var footerHeight = $("#nav-path").height();
  var windowHeight = $(window).height() - headerHeight - footerHeight;
  navtree.scrollTo('#selected',0,{offset:-windowHeight/2});
}

function expandNode(o, node, imm)
{
  if (node.childrenData && !node.expanded) 
  {
    if (!node.childrenVisited) 
    {
      getNode(o, node);
    }
    if (imm)
    {
      $(node.getChildrenUL()).show();
    } 
    else 
    {
      $(node.getChildrenUL()).slideDown("fast",showRoot);
    }
    if (node.isLast)
    {
      node.plus_img.src = node.relpath+"ftv2mlastnode.png";
    }
    else
    {
      node.plus_img.src = node.relpath+"ftv2mnode.png";
    }
    node.expanded = true;
  }
}

function getNode(o, po)
{
  po.childrenVisited = true;
  var l = po.childrenData.length-1;
  for (var i in po.childrenData) 
  {
    var nodeData = po.childrenData[i];
    po.children[i] = newNode(o, po, nodeData[0], nodeData[1], nodeData[2],
        i==l);
  }
}

function findNavTreePage(url, data)
{
  var nodes = data;
  var result = null;
  for (var i in nodes) 
  {
    var d = nodes[i];
    if (d[1] == url) 
    {
      return new Array(i);
    }
    else if (d[2] != null) // array of children
    {
      result = findNavTreePage(url, d[2]);
      if (result != null) 
      {
        return (new Array(i).concat(result));
      }
    }
  }
  return null;
}

function initNavTree(toroot,relpath)
{
  var o = new Object();
  o.toroot = toroot;
  o.node = new Object();
  o.node.li = document.getElementById("nav-tree-contents");
  o.node.childrenData = NAVTREE;
  o.node.children = new Array();
  o.node.childrenUL = document.createElement("ul");
  o.node.getChildrenUL = function() { return o.node.childrenUL; };
  o.node.li.appendChild(o.node.childrenUL);
  o.node.depth = 0;
  o.node.relpath = relpath;

  getNode(o, o.node);

  o.breadcrumbs = findNavTreePage(toroot, NAVTREE);
  if (o.breadcrumbs == null)
  {
    o.breadcrumbs = findNavTreePage("index.html",NAVTREE);
  }
  if (o.breadcrumbs != null && o.breadcrumbs.length>0)
  {
    var p = o.node;
    for (var i in o.breadcrumbs) 
    {
      var j = o.breadcrumbs[i];
      p = p.children[j];
      expandNode(o,p,true);
    }
    p.itemDiv.className = p.itemDiv.className + " selected";
    p.itemDiv.id = "selected";
    $(window).load(showRoot);
  }
}

