import csv
f = open("jobs.csv",'r')
reader = csv.reader(f)
new_rows_list = []
for row in reader:
    if (row[1]>"90000"):
        new_row = [row[0],row[1],'0']
        new_rows_list.append(new_row)
    elif(row[0]<"9000"):
        new_row = [row[0],row[1],'1']
        new_rows_list.append(new_row)
    else:
        new_row = [row[0],row[1],'2']
        new_rows_list.append(new_row)
f.close()

f2 = open("modified.csv",'w')
writer = csv.writer(f2)
writer.writerows(new_rows_list)
f2.close()
