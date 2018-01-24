#!usr/bin/env python
from setuptools import find_packages, setup

setup(name = 'BZOJCmd',
	version = '0.1',
	description = "A BZOJ crawer on Linux",
	long_description = "Read&Submit problems of BZOJ in Command Line",
	platforms = ["Linux"],
	author="Virgil von Einzbern",
	author_email="zhangche0526@gmail.com",
	url="https://zhangche0526.github.io",
	license = "MIT",
	packages = find_packages()
)
