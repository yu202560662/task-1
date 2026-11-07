# OpenCV 轮廓检测学习笔记（C++）

## 一、学习目标

掌握使用 OpenCV 进行图像轮廓检测的完整流程，包括轮廓查找、面积过滤、形状识别和边界框绘制。

## 二、核心概念

- **轮廓**：图像中物体边界的曲线表示，通常从二值图像中提取。
- **层级**：轮廓之间的嵌套关系，包括同级前后轮廓、子轮廓、父轮廓。
- **C++ 数据类型**：轮廓使用 `vector<vector<Point>>`，层级使用 `vector<Vec4i>`。

## 三、函数调用流程

### 1. 输入图像准备

- 读取图像并转为灰度图
- 进行二值化处理
- 准备一张用于绘制的图像

### 2. 调用 `findContours`

函数所需参数：

1. 输入图像（二值图像）
2. 轮廓 `contours`（输出结果）
3. 层级 `hierarchy`（输出结果）
4. 检索模式 `mode`
5. 近似方法 `method`

### 3. 绘制轮廓

使用 `drawContours` 函数：

- 指定目标图像
- 轮廓索引（`-1` 表示绘制全部）
- 颜色
- 线宽

### 4. 面积过滤

- 遍历每个轮廓，使用 `contourArea()` 计算面积
- 设置阈值过滤噪声（例如：面积 > 1000 才保留）

### 5. 形状识别

- 使用 `arcLength()` 计算周长
- 使用 `approxPolyDP()` 逼近多边形顶点数：
  - 3 个角点 → 三角形
  - 4 个角点 → 矩形 / 正方形
  - 更多角点 → 圆形

### 6. 边界框绘制

- 使用 `boundingRect()` 获取最小外接矩形坐标
- 存储到 `vector<Rect>` 容器中，便于批量处理

## 四、关键参数说明

### 检索模式（Mode）

| 模式 | 说明 |
|---|---|
| `RETR_EXTERNAL` | 仅检测最外层轮廓 |
| `RETR_LIST` | 检测所有轮廓，不建立层级关系 |
| `RETR_CCOMP` | 检测所有轮廓，组织成两级层级 |
| `RETR_TREE` | 检测所有轮廓，建立完整层级树 |
| `RETR_FLOODFILL` | 泛洪填充模式 |

### 轮廓近似方法（Method）

| 方法 | 说明 |
|---|---|
| `CHAIN_APPROX_NONE` | 存储轮廓上所有点 |
| `CHAIN_APPROX_SIMPLE` | 压缩水平、垂直和对角线段，只保留端点 |

### 层级结构（Hierarchy）

每个 `Vec4i` 元素包含 4 个整数值：

| 索引 | 含义 |
|---|---|
| `[0]` | 同一层级的下一个轮廓索引 |
| `[1]` | 同一层级的前一个轮廓索引 |
| `[2]` | 第一个子轮廓索引 |
| `[3]` | 父轮廓索引 |

没有对应项时值为 `-1`。

## 五、C++ 完整示例

```cpp
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

void getContours(cv::Mat imgDil, cv::Mat& img) {
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    // 1. 查找轮廓
    cv::findContours(imgDil, contours, hierarchy,
                     cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> conPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());

    for (size_t i = 0; i < contours.size(); i++) {
        // 2. 面积过滤
        double area = cv::contourArea(contours[i]);
        if (area < 1000) continue;

        // 3. 形状识别
        double peri = cv::arcLength(contours[i], true);
        cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

        int objCor = (int)conPoly[i].size();
        std::string objectType;

        if (objCor == 3) {
            objectType = "Triangle";
        } else if (objCor == 4) {
            cv::Rect rect = cv::boundingRect(conPoly[i]);
            float aspRatio = (float)rect.width / (float)rect.height;
            if (aspRatio > 0.95f && aspRatio < 1.05f) {
                objectType = "Square";
            } else {
                objectType = "Rectangle";
            }
        } else if (objCor > 4) {
            objectType = "Circle";
        }

        // 4. 绘制轮廓和边界框
        cv::drawContours(img, conPoly, i, cv::Scalar(255, 0, 255), 2);
        boundRect[i] = cv::boundingRect(conPoly[i]);
        cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(),
                      cv::Scalar(0, 255, 0), 2);
        cv::putText(img, objectType,
                    {boundRect[i].x, boundRect[i].y - 5},
                    cv::FONT_HERSHEY_SIMPLEX, 0.5,
                    cv::Scalar(0, 69, 255), 2);
    }
}
```

## 六、注意事项

- `findContours` 的输入必须是 **8 位单通道二值图像**。
- C++ 中 `findContours` 会修改输入图像，必要时先 `clone()`。
- OpenCV 4.x 中 `findContours` 只返回 `contours` 和 `hierarchy`，不再返回修改后的图像。
- C++ 需要先定义 `vector<vector<Point>>`、`vector<Vec4i>` 等变量，再传入函数。
- `approxPolyDP` 的 epsilon 参数影响识别精度，`0.02 * peri` 是常用经验值。
- 矩形与正方形需要结合 `boundingRect` 的宽高比进一步判断。
- 过滤阈值可以尝试动态方法，例如根据图像整体特征或参数随机范围调整，而不是完全依赖固定值。
- 紫色线条常用于轮廓可视化演示。

## 七、学习收获

完成了 **轮廓检测 → 面积过滤 → 形状分类 → 边界框绘制** 的完整闭环，能够有效去除图像中的噪声干扰。
