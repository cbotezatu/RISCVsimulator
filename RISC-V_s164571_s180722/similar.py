#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Dec  3 15:07:34 2018

@author: BotezatuCristian
"""

import os
import filecmp

dir = 'test_files'

res_files = [file for file in os.listdir(dir) if os.fsdecode(file).endswith(".res")]
for test_res_file in [file for file in os.listdir(dir) if os.fsdecode(file).endswith(".test_res")]:
    test_res_filename = os.fsdecode(test_res_file)
    res_filename = test_res_filename.split('.')[:-1][0] + ".res"

    if res_filename in res_files:
        file_comp = filecmp.cmp(dir + "/" + res_filename, dir + "/" + test_res_filename)
        print("and now testing: ", test_res_filename, ". Result: ", file_comp)
    else:
        print("res-file non-existing: ", test_res_filename)
