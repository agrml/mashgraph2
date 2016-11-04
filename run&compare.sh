#! /bin/bash

ex="/home/mikhail/.CLion2016.2/system/cmake/generated/mashgraph2-4ec1f8d6/4ec1f8d6/Debug/src/project2"
echo $ex
cd /Data/Dropbox/Study/University/Машграф/projects/mashgraph2

$ex -d data/multiclass/train_labels.txt -m model.txt --train
$ex -d data/multiclass/test_labels.txt -m model.txt -l predictions.txt --predict
./compare.py data/multiclass/test_labels.txt ./predictions.txt