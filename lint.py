#!/usr/bin/env python3

# SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
#
# SPDX-License-Identifier: MIT

import subprocess

if __name__ == '__main__':
	# reuse lint
	print('starting reuse lint...\n')
	reuseCmd = ['reuse', 'lint']
	try:
		subprocess.run(reuseCmd)
	except FileNotFoundError as e:
		if e.filename == 'reuse':
			print('reuse(https://reuse.software) not found.'
				' Make sure it is installed and in PATH.'
				'\nsee https://github.com/fsfe/reuse-tool')
		else:
			print(e)
	
	# cmake-lint
	print('\n\n')
	print('starting cmake lint...\n')
	gitNotIgnoredCmd = ["git", "ls-files"]
	fileList = subprocess.check_output(gitNotIgnoredCmd).splitlines()
	cmakeIgnoreList = [b'SoftwareList/extra_helper/', b'FormatterTarget/', b'cmake/CPM.cmake']
	cmakeFiles = []
	for f in fileList:
		for ign in cmakeIgnoreList:
			if ign in f:
				break
		else:
			if f.endswith(b'.cmake') or b'CMakeLists.txt' in f:
				cmakeFiles.append(f)
	cmakeLintCmd = ['cmake-lint']
	cmakeLintCmd.extend(cmakeFiles)
	try:
		subprocess.run(cmakeLintCmd)
	except FileNotFoundError as e:
		if e.filename == 'cmake-lint':
			print('cmake-lint(https://cmake-format.readthedocs.io/en/latest/cmake-lint.html) not found.'
				' Make sure it is installed and in PATH.'
				'\nsee https://cmake-format.readthedocs.io/en/latest/installation.html'
				' or https://github.com/cheshirekow/cmake_format')
		else:
			print(e)

	print('\n\n')
	print('reminder about clang-tidy and clazy')
