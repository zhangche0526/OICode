#!/usr/bin/env python  
# -*- coding:utf-8 -*-

from selenium import webdriver
from pyvirtualdisplay import Display

from bs4 import BeautifulSoup

def download_special(problem_id):
	print 'This problem is Speccial, please wait for a few seconds.'
	display = Display(visible=0, size=(800, 600))
	display.start()

	browser = webdriver.Firefox()
	browser.get('http://www.lydsy.com/JudgeOnline/loginpage.php')
	username = browser.find_element_by_xpath("//input[@name='user_id']")
	username.clear()
	username.send_keys("zhangche0526")
	password = browser.find_element_by_xpath("//input[@name='password']")
	password.clear()
	password.send_keys("68253301")
	browser.find_element_by_xpath("//input[@name='submit']").click()
	url = "http://www.lydsy.com/JudgeOnline/problem.php?id=" + str(problem_id)
	browser.get(url)
	soup = BeautifulSoup(browser.page_source,"html.parser")
	return soup


import requests
def download_general(problem_id):
	url = "http://www.lydsy.com/JudgeOnline/problem.php?id=" + str(problem_id)
	response=requests.get(url)
	soup = BeautifulSoup(response.text.encode(response.encoding).decode('utf8'),"html.parser")
	return soup

def craw(problem_id):
	soup=download_general(problem_id)
	if soup.find(class_='sampledata')==None:#Error Exception should be added here
		soup=download_special(problem_id)
	return soup

def parse_sample(soup):
	problem_title=soup.h2.string
	sample_input=''
	sample_output=''
	cnt=0
	for sample_data in soup.find_all(class_='sampledata'):
		for row in sample_data.children:
			if row.string!=None:
				if cnt==0:
					sample_input=sample_input+row.string
				else:
					sample_output=sample_output+row.string
		cnt=cnt+1
	return problem_title, sample_input, sample_output

import os
def check_sample(problem_id, exec_file_name):
	problem_title, sample_input, sample_output = parse_sample(craw(problem_id))
	input_file=open("data.in",'w')
	input_file.write(sample_input)
	input_file.close()
	output_file=open("data.out",'w')
	output_file.write(sample_output)
	output_file.close()
	os.system(exec_file_name+" < data.in > user.out")
	diff_result = os.system("diff -bB user.out data.out")
	print diff_result
	os.remove("data.in")
	os.remove("data.out")
	os.remove("user.out")
	
def print_help_msg():
	print "Usage:"
	print "\"-h\": Show this."

import sys, getopt
reload(sys) 
sys.setdefaultencoding('utf-8') 

opts, args = getopt.getopt(sys.argv[1:],"hc::")
for opt, val in opts:
	if opt=="-h":
		print_help_msg()
	if opt=="-c":
		check_sample(val, args[0])
