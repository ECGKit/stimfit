****************
The Python shell
****************

:Author: Christoph Schmidt-Hieber (christsc at gmx.de)
:Date: |today|

Why use Python?
===============
Why would you want to use Python (or more specifically [SciPy]_ ) to analyse neuroscientific data? Here are a couple of reasons:

* `Widely used <http://www.python.org/about/success/>`_, `general-purpose <http://www.python.org/about/>`_ programming language
* `Predicted to become the major programming language in neurosciences <http://www.frontiersin.org/neuroinformatics/specialtopics/8/>`_
* `About to replace hoc as the standard NEURON interpreter <http://www.frontiersin.org/neuroinformatics/paper/10.3389/neuro.11/001.2009/>`_, allowing to analyse the output from NEURON simulations in a single, integrated development environment
* `Favoured by the German Neuroinformatics Node as the standard neural data analysis language <http://www.sciencedirect.com/science?_ob=ArticleURL&_udi=B6T08-4SRCJN1-1&_user=125795&_rdoc=1&_fmt=&_orig=search&_sort=d&view=c&_acct=C000010182&_version=1&_urlVersion=0&_userid=125795&md5=3e6b8a3ab362b67480225d83cc17a9ef>`_
* has a reputation of having a `cleaner syntax <http://www.larssono.com/musings/matmatpy/index.html>`_ than most other scientific programming languages
* `Free software <http://www.python.org/psf/license/>`_

Before you start
================

If you are new to ``Python``, I suggest that you first have a look at the
[Python-tutorial]_. If that is not enough, abundant documentation is freely
available on the [Python-website]_. If you are new to `Stimfit <http://www.stimfit.org>`_, I recommend going through the tutorial in chapter 1 of this manual first.

The Python shell
================

When you start up `Stimfit <http://www.stimfit.org>`_,  you will find an embedded Python shell in
the lower part of the program window. From this shell, you have full
access to the Python interpreter. For instance, you could type:

::

    >>> stf.
 
which will pop up a window showing all the available functions from the
Stimfit module (abbreviated stf). For example, you could now check
whether a file is open by selecting the :func:`stf.check_doc()` function from that
list:

::

    >>> stf.check_doc()
    False

The function documentation will pop up when you type in the opening
bracket. The function returns the boolean False because you have not
opened any file yet. Since the stf module is imported in the namespace,
you can omit the initial ```stf.``` when calling functions. Thus, you
could get just the same result by typing

::

    >>> check_doc()
    False

If you press ```Ctrl+UP-arrow``` at the same time, you can go through
all the commands that you have previously typed in. This can be very
useful when you want to call a function several times in a row.

Accessing data from the Python shell
====================================

* **get_trace(trace=-1, channel=-1)**

The :func:`stf.get_trace()` function returns the currently displayed trace as 
one-dimension [NumPy]_ array when called without arguments:

::

    >>> a = get_trace()

You can now access individual sampling points using squared brackets to
specify the index. For example:

::

    >>> print a[123]
    -26.3671875

prints out the y-value of the sampling point with index 123. Note that
indices in ``Python`` are *zero-based*, i.e. the first sampling point
has the index 0.

::

    >>> print a[0]
    -21.2249755859

Python will check for indices that are out of range. For example,

::

    >>> print a[1e9]
    Traceback (most recent call last):
      File "<input>", line 1, in <module>
    IndexError: index out of bounds

You can use the :func:`stf.get_trace()` function to return any
trace within a file. The default values of trace = -1 and channel = -1
will return the currently displayed trace of the active channel. By
passing a value of 1 as the first argument, you could access the second
trace within your file (assuming it contains more than one trace
of course). Remember that indices are zero-based!

::

    >>> b = get_trace(1)
    >>> print b[234]
    >>> -23.7731933594

Using NumPy with Stimfit
========================
[NumPy]_ allows you to efficiently perform array computations from the ``Python`` shell. For example, you can multiply an array with a scalar:

:: 

    >>> a = get_trace()
    >>> print a[234]
    -27.0385742188
    >>> b = a*2
    >>> print b[234]
    -54.0771484375

Or multiply two arrays:

::

    >>> a = get_trace()
    >>> b = get_trace(1)
    >>> c = a*b
    >>> print a[234], "*",b[234], "=", c[234]
    -27.0385742188 * -23.7731933594 = 642.793253064
    
* **new_window()**

You can now display the results of the operation in a new window by passing a 1D-NumPy array to the :func:`stf.new_window()` function:

::

    >>> new_window(c)
    
The sampling rate and units will be copied from the window of origin. A short way of doing all of the above within a single line would have been:

::

    >>> new_window(get_trace() * get_trace(1))
    
* **new_window_matrix()**

You can pass a 2D-NumPy array to :func:`stf.new_window_matrix()`. The first dimension will be translated into individual traces, the second dimension into sampling points. This example will put the current trace and its square root into subsequent traces of a new window:

::

    >>> numpy_matrix = np.empty( (2, get_size_trace()) )
    >>> numpy_matrix[0] = get_trace()
    >>> numpy_matrix[1] = np.sqrt( np.abs(get_trace()) )
    >>> new_window_matrix(numpy_matrix)

In this example, np is the NumPy namespace. Typing np. at the command prompt will show you all available NumPy functions. :func:`stf.get_size_trace()` will be explained later on.

* **new_window_list()**

Although using a 2D_NumPy array is very efficient, there are a few drawbacks: the size of the array has to be known at construction time, and all traces have to be of equal lengths. Both problems can be avoided using :func:`stf.new_window_list()`, albeit at the price of a significant performance loss. :func:`stf.new_window_list()` takes a Python list of 1D-NumPy arrays as an argument:

::

    >>> python_list = [get_trace,]
    >>> python_list.append( np.concatenate( (get_trace(), get_trace()) ) )
    >>> new_window_list(python_list)

Note that items in Python list are written between *squared* brakes, and that a comma is required at the end of single-item lists.

The [SciPy]_ library, which is build on top of [NumPy]_, provides a huge amount of numerical tools, such as special functions, integration, ordinary differential equation solvers, gradient optimization, genetic algorithms or parallel programming tools. Due to its size, it is not packaged with `Stimfit <http://www.stimfit.org>`_ by default, but I highly recommend installing it for more advanced numerical analysis.

Control Stimfit from the Python shell
=====================================

Cursors
-------

Cursors can be positioned from the Python shell using one of the ``set_[xy]_start`` or ``set_[xy]_end`` functions, where ``[xy]`` stands for one of peak, base or fit, depending on which cursor you want to set. Correspondingly, the ``get_[xy]_start`` or ``get_[xy]_end`` functions can be used to retrieve the current cursor positions.

* **set_[xy]_start(pos, is_time = False)** and **set_[xy]_end(pos, is_time = False)** take one or two arguments. ``pos`` specifies the new cursor position. ``is_time`` indicates whether ``pos`` is an index, i.e. in units of sampling points (False, default), or in units of time (True), with the trace starting at t=0 ms. If there was an error, such as an out-of-bounds-index, these functions will return False.

* **get_[xy]_start(pos, is_time = False)** and **get_[xy]_end(pos, is_time = False)** optionally take a single argument that indicates whether the return value should be in units of sampling points (``is_time = False``,default) or in units of time (``is_time = True``). Again, traces start at t=0 ms. These functions will return -1 if no file is opened at the time of the function call. Indices can be converted into time values by multiplying with :func:`stf.get_sampling_interval()`. For example:

::

    >>> print "Peak start cursor index:", get_peak_start()
    Peak start cursor index: 254
    >>> print "corresponds to t =", get_peak_start(True), "ms"
    corresponds to t = 2.54 ms
    >>> print "=", get_peak_start()*get_sampling_interval(), "ms"
    = 2.54 ms
    >>> set_peak_start(10, True)
    True
    >>> print "new cursor position:", get_peak_start()
    new cursor position: 1000.0
    >>> print "at t =", get_peak_start(True), "ms"
    at t = 10 ms

The peak, baseline and latency values will not be updated until you either select a new trace, press **Enter** in the main window or call :func:`stf.measure()` from the Python shell.

Trace selection and navigation
------------------------------

* **select_trace(trace = -1)**

You can select any trace within a file by passing its zero-based index to :func:`stf.select_trace()`. The function will return ``False`` if there was an error. The default value of -1 will select the currently displayed trace as if you had pressed **S**. If you wanted to select every fifth trace, starting with an index of 0 and ending with an index of 9 (corresponding to numbers 1 to 10 in the drop-down box), you could do:

::

    >>> for n in range(0, 10, 5): select_trace(n)
    ...
    True
    True

Note that the Python range function omits the end point. 

* **unselect_all() select_all() get_selected_traces() new_window_selected_this()**

The list of selected traces can be cleared using :func:`stf.unselect_all()`, and conversely, all traces can be selected using :func:`stf.select_all()`. :func:`stf.get_selected_indices()` returns the indices of all selected traces as a Python tuple. Finally, the selected traces within a file can be shown in a new window using :func:`stf.new_window_selected_this()`.

* **get_size_trace(trace=-1, channel=-1)** and **get_size_channel(channel=-1)** 

Return the number of sampling points in a trace the number of traces in a channel, respectively. ``trace`` and ``channel`` have the same meaning as in :func:`stf.get_trace()`. These functions can be used to iterate over an entire file or to check ranges;


::

    >>> unselect_all(0
    >>> for n in range(0, get_size_channel(), 5): select_trace(n)
    True
    True
    >>> print get_selected_indices()
    (0, 5)
    >>> for n in get_selected_indices():
    ...     print "Length of trace", n, ":", get_size_trace(n)
    ...
    Length of trace 0 : 13050
    Length of trace 1 : 13050

* **set_trace(trace)**

sets the currently displayed trace to the specified zero-based index and returns ``False`` if there was an error. This will update the peak, base and latency values, so there is need to call :func:`stf.measure()` directly after this function.

* **get_trace_index()**

Correspondingly, :func:`stf.get_trace_index()` allows you to retrieve the zero-based index of the currently displayed trace. There is a slight inconsistency in function naming here: do not confound this function with :func:`stf.get_trace()`.

File I/O
--------
* **file_open(filename)** and **file_save(filename)**

will open or save a file specified by ``filename``. On windows, use double backslashes (\\\\) between directories to avoid conversion to special characters, such as \\t or \\n; for example:

::

    >>> file_save("C:\\data\\datafile.dat")

in Windows or

::

    >>> file_save("/home/cs/data/datafile.dat")
    
in GNU/Linux.

* **close_this()**

:func:`stf.close_this()` will close the currently displayed file, whereas

* **close_all()**

:func:`stf.close_all()` closes all open files.

Define your own functions
-------------------------
By defining your own functions, you can apply identical complex analysis to different traces and files. The following steps are required to make use of your own Python files:
 
1. Create a Python file in a directory that the Python interpreter will find. If you do not know where that is , use the Stimfit program directory (typically, this will be C:\\Program Files\\Stimfit in Windows or /usr/lib/phython2.5/site-packages/Stimfit in GNU/Linux, assuming that python 2.5 is your current python environment). You will find some example files in that directory that you can use as a template, but you should not touch stf.py which is the core Stimfit module.
2. Import the Stimfit module in your file:

::

    >>> import stf

3. Start `Stimfit <http://www.stimfit.org>`_ and import your file in the embedded Python shell. Assuming that your file is called ``myFile.py``, you would do:

::

    >>> import myFile

4. If you have applied changes to your file, there is no need to restart Stimfit. Just do:

::

    >>> reload(myFile)

To give you an example, this program shows a function that returns the sum of the squared amplitude values across all selected traces of a file.

::

    # import the Stimfit core module:
    import stf

    def get_amp():
       """ Returns the amplitude (peak-base)"""
       return stf.get_peak()-stf.get_base()
    
    def sqr_amp():
       """ Returns the sum of squared amplitudes of all
       selected traces, or -1 if there was an error. Uses
       the current settings for the peak direction and 
       cursor positions."""

       # store the current trace index:
       old_index = stf.get_trace_index()

       sum_sqr = 0
       for n in stf.get_selected_indices():
           # setting a trace will update all measurements
           # so there is no need to call measure()
           if not stf.set_trace(n):
               return -1
           sum_sqr += get_amp()**2

       # restore the displayed trace:
       stf.set_trace(old_index)

       return sum_sqr
        
        
To import and use this file, you would do:

::

    >>> import myFile
    >>> myFile.sqr_amp()
    497.70163353882447

.. note::

    You can import a file from any directory by selecting **File->Import Python module** or simpy by pressing ``Ctrl+I``. The file will be automatically loaded in the embedded Python shell and ready to be used (it is not necessary to type import(myFile). To reload the file, you have to select **File->Import Python module** or ``Ctrl+I`` again. 


Add a Python function to the Stimfit menu
-----------------------------------------

It is possible to create a submenu with your own Python functions in the ``Extensions`` menu of `Stimfit <http://www.stimfit.org>`__. To include your own function as a submenu you have to edit the file ``extensions.py``. This file is located in the Stimfit program folder. ``extensions.py`` contains a list called **extensionsList** that contains a list of submenus. For example, in the following example, only one submenu can be found, called *myAPCounter*:


:: 
    
    extensionList = [myAPCounter,]

To create a submenu we have first to define it as Extension. In ``extensions.py`` we should add:

::

    myAPCounter = Extension("Count APs", spells.count_aps, "Counts APs in selected traces", True) 

this command creates the extension called myAPCounter, which has the name "Counts APs" and executes the function spells.count_aps. If we add the extension *myAPCounter* to the extensionList, we will see now that a submenu appear within the Extension menu.
    
In general, an extension requires four arguments:

1. **Function name**: this is the name that will appear in the submenu (in our example this is "Counts APs").

2. **Python function**: the custom Python function to be executed when clicking on the submenu. We used here spells.counts_aps

3. **Description**: a more elaborate description of what the function is doing. We wrote "Counts APs in selected traces".

4. **Does your function require a file?**: If your function needs a file to be open type 'True', otherwise 'False'. Because our Python function operate on files, we typed 'True'.

.. note::

    Use a boolean return type when using your own Python functions in the extensions Menu. If you write a function that returns False upon failure, Stimfit will show a warning indicating that your custom function did not work propertly.  

Some recipes for commonly requested features
=============================================

Some often-requested features could not be integrated into the program easily without cluttering up the user interface. The following sections will show how the Python shell can be used to solve these problems.

Cutting traces to arbitrary lengths
-----------------------------------

Cutting traces is best done using the squared braked operators ([]) to slice a [NumPy]_ array. For example, if you wanted to cut a trace at the 100th sampling point, you could do:

::

    >>> a = get_trace()
    >>> new_window(a[:100])
    >>> new_window(a[100:])

In this example, a[:100] refers to a sliced NumPy array that comprises all sampling points from index 0 to index 99, and a[100:] refers to an array from index 100 to the last sampling point.

* **cut_traces(pt)** and **cut_traces_multi(pt_list)**

These functions cut all selected traces at a single sampling point (pt) or at multiple sampling points (pt_list). The cut traces will be shown in a new window. Both functions are included in the **stf namespace** from version 0.8.11 on. The code for :func:`stf.cut_traces()` is listed here. 

::

    import stf
    import numpy as np 

    def cut_traces( pt ):
        """Cuts the selected traces at the sampling point pt, 
        and shows the cut traces in a new window.
        Returns True upon success, False upon failure."""
        
        # Check whether anything has been selected:
        if not stf.get_selected_indices():
            print("Trace is not selected!")
            return False
        
        new_list = list()
        
        for n in stf.get_selected_indices():
            if not stf.set_trace(n): return False
                
        # Check for out of range:
        if pt < stf.get_size_trace():
            new_list.append( stf.get_trace()[:pt] )
            new_list.append( stf.get_trace()[pt:] )
            
        else:
            print "Cutting point", pt, "is out of range"
        
        # Don't create a new window if everything was out of range
        if len(new_list) > 0: 
            return stf.new_window_list( new_list )
        else:
            return False
            
For example:

::

    >>> dt = stf.get_sampling_interval()
    >>> cutPoints = [int(100/dt), int(900/dt)]
    >>> cut_traces_multi(cutPoints) 

will cut all selected traces at time 100 and 900 (in units of the x axis) and show the cut traces in a new window. Note that you can pass a list or a tuple as argument.

::

    >>> cut_traces_multi(range(100,2000,100)) # cut at 100 sampling points not ms!

will cut the selected traces at every 100th sampling point, starting with the 100th and ending with the 1900th.

.. [Python-tutorial] http://docs.python.org/tut/
.. [Python-website]  http://www.python.org/doc/
.. [NumPy] http://numpy.scipy.org/
.. [SciPy] http://www.scipy.org/
