import csv

with open('openClose.csv', 'w', newline='') as csvfile:
    spamwriter = csv.writer(csvfile, delimiter=' ',
                            quotechar='|', quoting=csv.QUOTE_MINIMAL)
    spamwriter.writerow(['Spam'] * 5 + ['Baked Beans'])
    spamwriter.writerow(['Spam', 'Lovely Spam', 'Wonderful Spam'])

    id, roll, yaw, pitch, p19x, p19y, p20x, p20y, p21x, p21y, p22x, p22y, p23x, p23y, p24x, p24y, p25x, p25y, p26x, p26y, p27x, p27y, p28x, p28y, p29x, p29y, p30x, p30y, state