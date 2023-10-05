from sklearn import linear_model
import csv
import numpy as np
from micromlgen import port

x = []
y = []
z = []
d = []
labels = []

with open("prostate.csv", newline='') as f:
    ctx = csv.DictReader(f, delimiter=';')
    for row in ctx:
        if row["PSA_level"] != " ":
            try:
                int(row["PSA_level"])
            except ValueError:
                if row["PSA_level"][0] == ",":
                    x.append(0)
                else:
                    x.append(int(row["PSA_level"].split(",")[0]))
            else:
                x.append(int(row["PSA_level"]))
            y.append(int(row["Bone_metastasis"]))
            z.append(int(row["Chemotherapy"]))
            d.append(int(row["\ufeffDate_Dx"].split('/')[-1]))
            labels.append(int(row["Time_to_death"]))

x= np.array(x)
y = np.array(y)
z = np.array(z)
d = np.array(d)
labels = np.array(labels)

train_dt = np.stack((x,y,z,d), 1)

regr = linear_model.LinearRegression().fit(train_dt, labels)

with open('prediction.h', 'w') as f:
    f.write(port(regr))
