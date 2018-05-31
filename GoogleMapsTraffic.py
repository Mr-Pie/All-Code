import http.client
import time

while True:
    conn = http.client.HTTPSConnection("maps.googleapis.com")
    conn.request("GET", "/maps/api/distancematrix/json?origins=-37.781027,145.024719&destinations=-37.766315,145.027382&departure_time=now&traffic_model=best_guess&mode=driving&key=AIzaSyAXaC6iMpWHCjoIUZ2JAeT-IQ_Oi4gdv8Y")
    r1 = conn.getresponse()
    #print(r1.status, r1.reason)
    data1 = r1.read()
    #print(data1)
    text = b'duration_in_traffic'
    location = data1.find(text)
    value = data1[location:]
    #print(value)
    newtext = b'value'
    newlocation = value.find(newtext)
    newstring = value[newlocation:]
    #print(newstring)
    findend = b'\n'
    endlocation = newstring.find(findend)
    finalvalue = newstring[9:endlocation]
    #print(finalvalue)
    mystring = int(finalvalue)
    print(mystring)
    if mystring > 530:
        print('HIGH')
    else:
        print('LOW')
    time.sleep(10)
 

conn.close()
