# K-Means Clustering
K-Means clustering implemented in `C++`. Based on C. M. Bishop's book [Pattern Recognition and Machine Learning](https://www.microsoft.com/en-us/research/uploads/prod/2006/01/Bishop-Pattern-Recognition-and-Machine-Learning-2006.pdf) (2006).

## Table of contents
- [Testing on Old Faithful dataset](#Old-faithful-dataset)
- [Testing on Iris dataset](#Iris-dataset)
- [Image Segmentation](#Image-segmentation)

## Old Faithful dataset
The algorithm was tested on the [Old Faithful](https://gist.github.com/curran/4b59d1046d9e66f2787780ad51a1cd87) dataset, by running the algorithm for 10 epochs and setting `k = 2`.

![Results](https://user-images.githubusercontent.com/50104866/147732730-7b57fc9d-6a0d-4167-9edf-f90eee04e476.png)

The green stars show the cluster means after 10 epochs.

## Iris dataset
The algorithm was tested on the [Iris](https://www.kaggle.com/datasets/arshid/iris-flower-dataset) dataset, consisting of 50 samples from each of three species of Iris (Iris Setosa, Iris virginica, and Iris versicolor). Four features are measured for each sample. However, only the first three features are used for classification, thus `k = 3`. The algorithm was executed for 10 epochs.

![iris-3d](https://user-images.githubusercontent.com/50104866/174447457-67512d3c-f703-4fe3-aa87-fac46c458268.png)

The red stars show the cluster means after 10 epochs.

## Image segmentation

The image segmentation is achieved by clustering all pixel values of the image with K-Means clustering and expressing each pixel's value as the mean of the cluster it is assigned to. Different `k` values give different degrees of compression.

| `k = 2` | `k = 3` |
| :---:| :---:|
| ![k2](https://user-images.githubusercontent.com/50104866/147850348-e0e39a07-8423-4041-a415-250e997a8c91.png)| ![k3](https://user-images.githubusercontent.com/50104866/147826186-b160e4ee-27f7-4ede-8666-3de4c8e68795.png) |
| `k = 10` | `k = 20` |
| ![k10](https://user-images.githubusercontent.com/50104866/147826188-c05b83d3-21bc-4a1d-8572-805097fd7289.png)| ![k20](https://user-images.githubusercontent.com/50104866/147826189-8bc435d0-a206-4d23-93e7-751e628d35cb.png) |
