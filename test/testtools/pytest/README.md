The way this test system works is there is a python script which calls a 
compiled C++ executable. You should edit `test.ini` with the parameters you 
want for your test, and `ini_path` in `pytest.py` so that the script can find 
the `.ini` file from where you're calling it. The `.ini` file is set up so that you
can run tests with linear changes in the parameters.

Run `pytest.py` and it will create an output directory as specified in `test.ini`
where result data will go. By default it will save a `.csv` with the raw data, and
you can edit `use_data` in `py_test.py` to save graphs and whatever you would want.