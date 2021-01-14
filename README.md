# HiddenSurfaceRemover

## 简介

本程序实现了普通Z-Buffer、扫描线Z-Buffer、普通层次Z-Buffer以及带场景八叉树的层次Z-Buffer四种算法。
并将它们用于三维模型的渲染。

## 开发环境

本程序的开发环境如下表所示。

|项目|值|
|:---:|:---:|
|CPU|Intel® Core™ i7-8550U|
|内存|7.7GB|
|操作系统|Manjaro Linux|

本程序开发时用到的一些软件和库以及它们的版本如下表所示。

|软件/库|版本|
|:---:|:---:|
|Linux内核|5.4.85|
|GCC|10.2.0|
|CMake|3.17.5|
|Assimp|5.0.1|
|glm|0.9.9.8|
|Qt|5.15.2|

## 使用说明

- 编译并运行程序后，可以点击窗口左上角的按钮选择要绘制的模型文件，支持的模型文件格式详见Assimp库的文档。
- 选择模型文件后，绘制的结果会显示在窗口右侧的部分。
- 在绘制部分点击鼠标左键或右键并拖动，可以对模型进行旋转；滑动鼠标滚轮，可以对模型进行缩放。
- 在左侧的单选框还可以对使用的Z-Buffer算法进行选择，每次选择后，模型都会被重新绘制，旋转和缩放会被重置。
- 单选框下方会显示模型的顶点数、面元数以及渲染一帧所用的时间。

## 运行截图

![](screenshot/1.png "文件选择界面")

![](screenshot/2.png "主界面")

![](screenshot/3.png "旋转及缩放后的模型")

## 类说明

程序中的一些主要的类及它们的说明如下表所示。

|类|说明|
|:---:|:---:|
|ZBuffer|Z-Buffer算法的基类|
|NaiveZBuffer|普通Z-Buffer算法|
|ScanlineZBuffer|扫描线Z-Buffer算法|
|NaiveHierarchicalZBuffer|普通层次Z-Buffer算法|
|OctreeHierarchicalZBuffer|带场景八叉树的层次Z-Buffer算法|
|Polygon|多边形|
|ActivePolygon|活化多边形|
|Edge|多边形的边|
|ActiveEdge|活化边|
|Segment|扫描线与多边形的相交线段|
|ActiveSegment|活化线段|
|QuadTree|层次Z-Buffer，即四叉树|
|Octree|场景八叉树|
|Model|用于存储三维模型|

## 算法比较

在model文件夹中存放了用于比较的模型，它们所含的顶点数和面元数如下表所示。

|模型文件|顶点数|面元数|
|:---:|:---:|:---:|
|cube.obj|36|12|
|suzanne.obj|2904|968|
|bunny.obj|208890|69630|
|armadillo.obj|637721|212574|

各个模型使用各种算法绘制所需的时间如下表所示。

|用时(ms)|cube.obj|suzanne.obj|bunny.obj|armadillo.obj|
|:---:|:---:|:---:|:---:|:---:|
|普通Z-Buffer算法|111|82|256|327|
|扫描线Z-Buffer算法|81|61|254|446|
|普通层次Z-Buffer算法|647|585|1107|983|
|带场景八叉树的层次Z-Buffer算法|661|555|1001|1358|