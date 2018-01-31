#!/usr/bin/env python  
# -*- coding:utf-8 -*-

def print_error(msg, no_new_line = False):
	if no_new_line == True:
		print "\033[1;31m"+msg+"\033[0m",
	else:
		print "\033[1;31m"+msg+"\033[0m"

def print_normal(msg, no_new_line = False):
	if no_new_line == True:
		print "\033[1;34m"+msg+"\033[0m",
	else:
		print "\033[1;34m"+msg+"\033[0m"

def print_ok(msg, no_new_line = False):
	if no_new_line == True:
		print "\033[1;32m"+msg+"\033[0m",
	else:
		print "\033[1;32m"+msg+"\033[0m"

from selenium import webdriver
from pyvirtualdisplay import Display

from bs4 import BeautifulSoup

def download_special(problem_id):
	display = Display(visible=0, size=(800, 600))
	display.start()

	browser = webdriver.Firefox()
	browser.get('http://www.lydsy.com/JudgeOnline/loginpage.php')
	username = browser.find_element_by_xpath("//input[@name='user_id']")
	username.clear()
	username.send_keys("Karen")
	password = browser.find_element_by_xpath("//input[@name='password']")
	password.clear()
	password.send_keys("68253301")
	browser.find_element_by_xpath("//input[@name='submit']").click()
	url = "http://www.lydsy.com/JudgeOnline/problem.php?id=" + str(problem_id)
	browser.get(url)
	soup = BeautifulSoup(browser.page_source,"html.parser")
	del display
	del browser
	return soup

import requests
def download_general(problem_id):
	url = "http://www.lydsy.com/JudgeOnline/problem.php?id=" + str(problem_id)
	response=requests.get(url)
	soup = BeautifulSoup(response.text.encode(response.encoding).decode('utf8'),"html.parser")
	return soup

def craw_problem(problem_id):
	soup=download_general(problem_id)
	if soup.find(class_='sampledata')==None:#Error Exception should be added here
		soup=download_special(problem_id)
	return soup

def submit_solution(problem_id, source_code):
	display = Display(visible=0, size=(800, 600))
	display.start()

	browser = webdriver.Firefox()
	browser.get('http://www.lydsy.com/JudgeOnline/loginpage.php')
	username = browser.find_element_by_xpath("//input[@name='user_id']")
	username.clear()
	username.send_keys("Karen")
	password = browser.find_element_by_xpath("//input[@name='password']")
	password.clear()
	password.send_keys("68253301")
	browser.find_element_by_xpath("//input[@name='submit']").click()

	browser.get('http://www.lydsy.com/JudgeOnline/problem.php?id='+str(problem_id))
	soup = BeautifulSoup(browser.page_source,"html.parser")

	browser.get("http://www.lydsy.com/JudgeOnline/submitpage.php?id="+str(problem_id))
	browser.find_element_by_xpath("//textarea[@name='source']").send_keys(source_code)
	browser.find_element_by_xpath("//input[@value='Submit']").click()

	del display
	del browser
	return soup

def craw_judge_result(browser):
	url = "http://www.lydsy.com/JudgeOnline/status.php?user_id=zhangche0526"
	browser.get(url)
	soup = BeautifulSoup(browser.page_source,"html.parser")
	return soup

def parse_judge_result(soup):
	status_row = soup.find(class_='evenrow')
	result_list = ['', '', '', '']
	cnt=0
	for child in status_row.children:
		if cnt == 3:
			for s in child.children:
				result_list[1] = s.string
		if cnt == 4:
			result_list[2] = child.text
		if cnt == 5:
			result_list[3] = child.text
			break
		cnt += 1
	return status_row, result_list

def print_result(result_list):
	if(result_list[1] == "Accepted"):
		print_ok(result_list[1], True)
	else:
		print_error(result_list[1] ,True)
	print_normal(result_list[2], True)
	print_normal(result_list[3])
	
import pyperclip
import time
def judge_online(problem_id, source_file_name = None):
	if source_file_name == None:
		source_file_name = problem_id+".cpp"
	if os.path.isfile(source_file_name) == False:
		print_error("Souce file not found")
		return
	source_code = open(source_file_name).read()
	problem_title = submit_solution(problem_id, source_code).h2.string
	time.sleep(1)
	
	display = Display(visible=0, size=(800, 600))
	display.start()
	browser = webdriver.Firefox()
	status_row, result_list = parse_judge_result(craw_judge_result(browser))
	while(result_list[1] == "Pending" or result_list[1] == "Running_&_Judging" or result_list[1] == "Compiling"):
		status_row, result_list = parse_judge_result(craw_judge_result(browser))
		time.sleep(2)
	del display
	del browser
	print problem_title
	print_result(result_list)
	if result_list[1] != "Accepted":
		pyperclip.copy(str(status_row))

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
def check_sample(problem_id, source_file_name = None):
	if source_file_name == None:
		source_file_name = problem_id+".cpp"
	if os.path.isfile(source_file_name) == False:
		print_error("Souce file not found")
		return
	print "Getting Sample..."
	problem_title, sample_input, sample_output = parse_sample(craw_problem(problem_id))
	input_file=open("data.in",'w')
	input_file.write(sample_input)
	input_file.close()
	output_file=open("data.out",'w')
	output_file.write(sample_output)
	output_file.close()
	exec_file_name=problem_id+".exec"
	print "Compiling..."
	complie_result = os.system("g++ "+source_file_name+" -o "+exec_file_name)
	if(complie_result != 0):
		print_error("Compile_Error")
		return
	print "Running..."
	run_result = os.system("./"+exec_file_name+" < data.in > user.out")
	if(run_result != 0):
		print_error("Runtime_Error")
		return
	diff_result = os.system("diff -bB user.out data.out")
	if(diff_result == 0):
		print_normal("Good! Your programe has just passed the sample.");
	else:
		print_error(str(diff_result))
	os.remove("data.in")
	os.remove("data.out")
	os.remove("user.out")
	os.remove(exec_file_name)
	
def print_help_msg():
	print "Usage:"
	print "\"-h\": Show this."

import sys, getopt
reload(sys) 
sys.setdefaultencoding('utf-8') 

opts, args = getopt.getopt(sys.argv[1:],"hc::s::")
for opt, val in opts:
	if opt == "-h":
		print_help_msg()
	if opt == "-c":
		if len(args) == 0:
			check_sample(val)
		else:
			check_sample(val, args[0])
	if opt == "-s":
		if len(args) == 0:
			judge_online(val)
		else:
			judge_online(val, args[0])
