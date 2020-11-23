# Add Spark Python Files to Python Path

import os
import sys

SPARK_HOME = os.environ["SPARK_HOME"]  # Add Spark path
os.environ["SPARK_LOCAL_IP"] = "127.0.0.1:80"  # Set Local IP
sys.path.append(SPARK_HOME + "/python")  # Add python files to Python Path

print(sys.path)
import numpy as np
from pyspark import SparkConf, SparkContext
from pyspark.mllib.classification import LogisticRegressionWithSGD, LabeledPoint


def getSparkContext():
    """
    Gets the Spark Context
    """
    return SparkContext(
        conf=(
            SparkConf()
            .setMaster("local[4]")  # run on local
            .setAppName("Logistic Regression")  # Name of App
            .set("spark.executor.memory", "1g")
        )  # Set 1 gig of memory
    )


def mapper(line):
    """
    Mapper that converts an input line to a feature vector
    """
    feats = [float(f) for f in line.strip().split(",")]
    return LabeledPoint(feats[-1], feats[:-1])


# print(dir(LabeledPoint(1, [1])))
# raise SystemExit

sc = getSparkContext()

# Load and parse the data
data = sc.textFile(os.environ["DATA"])
parsedData = data.map(mapper)


# Train model
model = LogisticRegressionWithSGD.train(parsedData)

# Predict the first elem will be actual data and the second
# item will be the prediction of the model
labelsAndPreds = parsedData.map(
    lambda point: (int(point.label), model.predict(point.features))
)

# Evaluating the model on training data
trainErr = labelsAndPreds.filter(lambda x: x[0] != x[1]).count() / float(
    parsedData.count()
)

# Print some stuff
print("Error Rate =", trainErr)
