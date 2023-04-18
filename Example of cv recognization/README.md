### Paper-Piano
### Hand detection  
An example of hand detection is as follows ：    
* Picture example：  
![image](https://user-images.githubusercontent.com/127966120/231716160-4ae48bb1-f2a4-4666-8588-a797e955b1ee.png)    

## Project configuration
* Author's development environment:
*Python 3.7
* PyTorch >= 1.5.1

## Data set   
### Hand detection data set
The project dataset was produced using TV-Hand and COCO-Hand (part of COCO-Hand-Big).
TV-Hand and COCO-Hand dataset official website address http://vision.cs.stonybrook.edu/~supreeth/
```
Thanks to the dataset contributors.
Paper:
Contextual Attention for Hand Detection in the Wild. S. Narasimhaswamy, Z. Wei, Y. Wang, J. Zhang, and M. Hoai, IEEE International Conference on Computer Vision, ICCV 2019.
```
* [Dataset download address of the training set produced by this project (Baidu SkyDrive Password: c680 )](https://pan.baidu.com/s/1H0YH8jMEXeIcubLEv0W_yw)

### The data format of the dataset
size is the resolution of the whole image, (x, y) is the normalized coordinates of the center of the target object to the whole image, w, h are the normalized width and height of the bounding box of the target object to the whole image.

```
dw = 1./(size[0])
dh = 1./(size[1])
x = (box[0] + box[1])/2.0 - 1
y = (box[2] + box[3])/2.0 - 1
w = box[1] - box[0]
h = box[3] - box[2]
x = x*dw
w = w*dw
y = y*dh
h = h*dh
```

In order to better understand the label data format, you can run the show_yolo_anno.py script to make the format of the dataset. Pay attention to the path and path_voc_names in the configuration script, path is the relevant file path of the labeled dataset, and path_voc_names is the dataset configuration file.
### Make your own training dataset
* As shown below, each row represents an object instance, the first column is the label, followed by the normalized center coordinates (x, y), and the normalized width (w) and height (h), and each column Information space interval. The normalization formula is as above, and at the same time, after parameter adaptation through show_yolo_anno.py, its correctness can be verified visually.
```
label x y w h
0 0.6200393316313977 0.5939000244140625 0.17241466452130497 0.14608001708984375
0 0.38552491996544863 0.5855700073242187 0.14937006832733554 0.1258599853515625
0 0.32889763138738515 0.701989990234375 0.031338589085055775 0.0671400146484375
0 0.760577424617577 0.69422998046875 0.028556443261975064 0.0548599853515625
0 0.5107086662232406 0.6921500244140625 0.018792660530470802 0.04682000732421875
0 0.9295538153861138 0.67602001953125 0.03884511231750328 0.01844000244140625
```

### Hand detection pre-training model
* Including yolo pre-training model image input size 416, yolo-tiny pre-training model image input size 512.
* [Pre-training model download address (Baidu network disk Password: 7mk0 )](https://pan.baidu.com/s/1hqzvz0MeFX0EdpWXUV6aFg)


## How to use the project

### Dataset Visualization
* Run the command in the root directory: show_yolo_anno.py (note the configuration of relevant parameters in the script)

### Model training
* Run the command in the root directory: python train.py (note the configuration of relevant parameters in the script)

* Note: The key code segment for loading the training configuration parameters is as follows, cfg/transport.data is the configuration parameter file for training the coco vehicle dataset.
```
if __name__ == '__main__':
     train(data_cfg = "cfg/transport.data")
```

* The "*.data" file under the cfg folder contains important configuration information, take "cfg/transport.data" as an example as follows:
```
cfg_model=yolo # Model selection: yolo / yolo tiny
classes=8 # the categories of the dataset
gpus = 0 # GPU selection
num_workers = 8 # The number of processes of the data iterator (enhancer) during training
batch_size = 8 # Set the number of pictures for each batch during training, this example is 8 pictures
img_size = 416 # The default input image size of the model is 416*416
multi_scale = True # Whether to use multi-scale enhancement in training, this example is using
epochs = 100 # The total training cycle, a complete traversal of the data set is a cycle
train=./yolo_transport_train/anno/train.txt # train.txt path of the training set
valid=./yolo_transport_train/anno/train.txt # The train.txt path of the verification set, the verification function code is not added to the current training code
names=./cfg/transport.names # The specific category name corresponding to the data set needs to correspond to its label
finetune_model = ./weights-yolov3-transport/latest_416.pt # The pre-trained model used
lr_step = 10,20,30 # Update the learning rate when training for a specific epoch
lr0 = 0.001 # Initial learning rate during training

```
