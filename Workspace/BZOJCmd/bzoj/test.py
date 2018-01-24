#!/usr/bin/env python  
# -*- coding:utf-8 -*-
import sys

from selenium import webdriver
from pyvirtualdisplay import Display

from bs4 import BeautifulSoup
def download_special(problem_id):
	print 'This problem is QuanXianTi, please wait for a few seconds.'
	display = Display(visible=0, size=(800, 600))
	display.start()

	browser = webdriver.Firefox()
	browser.get('http://www.lydsy.com/JudgeOnline/loginpage.php')
	username = browser.find_element_by_xpath("//input[@name='user_id']")
	username.clear()
	username.send_keys("zhangche0526")
	password = browser.find_element_by_xpath("//input[@name='password']")
	password.clear()
	password.send_keys("")
	browser.find_element_by_xpath("//input[@name='submit']").click()
	url = "http://www.lydsy.com/JudgeOnline/problem.php?id=" + str(problem_id)
	browser.get(url)
	soup = BeautifulSoup(browser.page_source,"html.parser")
	return soup

def submit_solution(problem_id, source_code):
	display = Display(visible=0, size=(800, 600))
	display.start()

	browser = webdriver.Firefox()
	browser.get('http://www.lydsy.com/JudgeOnline/problem.php?id='+problem_id)
	exec_js = 'document.getElementById("frame_source").contentWindow.document.body.innerHTML="%s"' %(source_code)
	browser.execute_script(exec_js)

	browser.find_element_by_xpath("//input[@value='Submit']").click()
	url = "http://www.lydsy.com/JudgeOnline/status.php?user_id=zhangche0526"
	browser.get(url)
	soup = BeautifulSoup(browser.page_source,"html.parser")

def parse_judge_result(problem_id, soup):
	status_row = soup.find(class_='evenrow')
	result_list = ['']
	result_list[0] = craw(problem_id).h2.string
	result_list[1] = status_row.children[3].children[0].string
	result_list[2] = status_row.children[4].string + "kB"
	result_list[3] = status_row.children[5].string + "ms"
	return status_row, result_list

def online_judge(problem_id, source_code):
    status_row, result_list     
    result_col_name_list = ['Problem','Status', '']


def print_data(soup):
	cnt=0
	print soup.h2.string
	for sample_data in soup.find_all(class_='sampledata'):
		if cnt==0:
			print "\033[34;0mSample Input"
		else :
			print "\033[34;0mSample Output"
		for row in sample_data.children:
			if row.string!=None:
				print row.string
		cnt=cnt+1

import requests
def download_general(problem_id):
	url = "http://www.lydsy.com/JudgeOnline/problem.php?id=" + str(problem_id)
	response=requests.get(url)
	soup = BeautifulSoup(response.text.encode(response.encoding).decode('utf8'),"html.parser")
	return soup

def craw(problem_id):
	soup=download_general(problem_id)
	if soup.find(class_='sampledata')==None:
		soup=download_special(problem_id)
	print_data(soup)

reload(sys) 
sys.setdefaultencoding('utf-8') 

craw(sys.argv[1])
