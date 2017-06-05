#!/usr/bin/env python2.7

import cv 

# get orginal image
orig = cv.LoadImage('cake.png')

# show original 
cv.ShowImage("orig", orig)

# convert to hsv and get just hue
hsv = cv.CreateImage(cv.GetSize(orig), 8, 3) 
hue = cv.CreateImage(cv.GetSize(orig), 8, 1) 
sat = cv.CreateImage(cv.GetSize(orig), 8, 1) 
val = cv.CreateImage(cv.GetSize(orig), 8, 1) 
cv.CvtColor(orig, hsv, cv.CV_RGB2HSV)
cv.Split(hsv,hue,sat,val,None)
#cv.ShowImage("hue", hue)

# loop to find how many different hues are present...
query = cv.CreateImage(cv.GetSize(orig), 8, 1) 
result = cv.CreateImage(cv.GetSize(orig), 8, 1) 
for i in range(0,255):
  cv.Set(query,i)
  cv.Cmp(query,hue,result,cv.CV_CMP_EQ)
  # if a number of pixels are equal - show where they are 
  if (cv.CountNonZero(result)>1000): # <-what is signficant?
    cv.ShowImage(str(i),result)
    cv.SaveImage(str(i)+".png",result)
    cv.WaitKey(-1)
