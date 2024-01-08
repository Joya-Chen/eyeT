#!/usr/bin/env python
# -*- coding: utf-8 -*-
import requests
import time
def hello():
    print("hello world!")
    return

def show(str):
    return str

def add(a, b):
    return a + b

def upload(serverUrl,pwd,dataInfo,filePath,returnPath,time_out):
    print(serverUrl,",",pwd,",",dataInfo,",",filePath,",",returnPath,",",time_out)
    now=time.ctime()
    my_data = {"DataGUID":pwd, "DataInfoNo":dataInfo,"ClientTime":now}
    url = serverUrl
    f=open(filePath,'rb')
    files = {'file':f}
    rText=""
    try:
        r = requests.post(url=url,files=files,data = my_data,timeout=time_out)
        r.raise_for_status()
        print(r.text)
        rText = str(r.text)
    except requests.exceptions.Timeout as errt:
           print ("Timeout Error:",errt)
           rText = "Timeout Error :"+str(errt)
    except requests.exceptions.HTTPError as errh:
           print ("Http Error:",errh)
           rText = "Http Error :"+str(errh)
    except requests.exceptions.ConnectionError as errc:
           print ("Error Connecting :Should check the network first.")
           rText =str("Error Connecting :Should check the network first.")
    except requests.exceptions.RequestException as erre:
           print ("OOps: Something Else ",erre)
           rText = "OOps: Something Else "+str(erre)
    finally:
           f.close()
           path = returnPath
           f=open(path,'w')
           f.write(str(rText))
           f.close()
    return rText
