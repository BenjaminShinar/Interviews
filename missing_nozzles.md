# Missing Nozzles Refactor

## Actors
* dps subsystem: manager, handler, accessor
* qcs,test driver and other external subsystems
* database
* missing nozzles handler, missing nozzles bar handlers, missing nozzles helper class

## What are missing Nozzles?
In a printing system, each color is mounted on a bar. each bar contains printing heads, each printing head contains nozzles. the nozzles are what 'shoots' out the ink. a nozzle is a hole that's about a pixel wide, and it can be damaged, shifted, malfunction in all kinds of ways.  
If a nozzle isn't working properly, we can compensate for it using it's neighbors, they can pick up the slack for it.  
our module was designed to handle this situation: we identify which nozzles to compensate for, based both on raw data and according to decision algorithms.


## Requirements - Why did we change the system
The previous system relied on external sources to make the decisions, it was simply a pipe between the raw data and the controller. it wasn't able to validate complex data, identify possible problems in the data (it might be corrupted), and to account for differnt expecations for printing quality (customer A might require much higher printing quality than customer B).  
The refactor was meant to allow us to meet new requests and to prepare an infrastructure for future demands.

## Parts
All parts of the program can interact with the **database** (get and set parameters), some of them are notified when parts of it are changed.

The **manager** recieves infomartion from any number of external subsystems, this layer controls the exposed API.
The **handler** interacts with the manager, this layer embodies the business logic of the program
The **accessor** interacts with the manager, this layer commuincates with the controller.

the handler and accessor contain respective bar handlers and bar accessors. each bar coresponds to a color. the bar handlers control the business logic that is independent from other bars, while the main handler requests and aggregates the responses from the bar handlers, and controls the business logic that relates to more than one bar. any number of components can reuse this structure, without getting in the way of other modules (*the main bar handlers control the printing activity*).

following the design described above, we have a single **missing nozzles handler** and several **missing nozzles bar handlers**. Those classes contain the actual logic relating to missing nozzles operations.  
The **missing nozzles helper** component controls operations relating to mediating between the form the data is stored in the database (a byte array that has been encoded to reduce its' size) and the runtime form (an object that contains 50k nozzle objects). 


## Basic Flow
* recive a correction / calibration data regarding missing nozzles. this is a snapshot of the current state of the machine.
    * online correction from a different subsystem.
    * corrections from a file.
    * manual corrections from the ui.
    * exposed API from the testing project.
* analyze the incoming data compared to the existing data, perform corrections as needed.
    * replacing or adding data.
    * validating data.
    * which algorithms are used.
* decide whether to accept the new data or reject it.
    * accept or reject all the data (all bars) or some of them.
    * if reject, restore system to previous state.
* handle the result (reject or accept).
    * forward the accepted data.
    * respond with a detailed explainnation of the rejection reason.


## design paterns?
* Decorator - some algorithms could be used togehter or apart, but they had to be sequecial. so we built objects with decorator levels, so if some algorithm isn't needed, we don't build that layer.
* Builder - we seperated the construction/storage/retrival logic from the usage logic.
* Adapter - transform the different forms of incoming data into a common form. account for missing data (from UI) but still use the same behavior.

## My contribution
The refactor started as a team project (four people), with the design decisions being done by the team leader and the senior developer. my initial role was the handling the logging and exporting of data, implementaing the cross bars logic in the missing nozzles handler (aggregate results from the bars), and creating the tests for the changes.  
As the project continued and we recived more requests for changes and features (more algorithms, differnitation between customers, concerns about storage), I got involved with more and more of the module. eventually, I had to write a guide and present it to the team when I left the job.


### Example - Database Operations
In the old system, there was no mechanism to say if the correction was a failure or success, if we recieved data and we could parse it into the database, it was a success. if we failed, it was an indication of either a programming bug or one of the subsystems was offline. in the refactored system, we needed to apply validation on the data integrity.  
If one bar failed, we might decide to roll back the entire operation, which would require probing the database and rebuilding the object (multiple requests to a shared object with it's own locks). We solved this issue by seperating the data from the class, so each object held a copy of the data stored by the database, and could rebuild itself from it independtly. So at any point during the correction, we could command a bar to restore itself to the last acceptble state.  
This ability proved crucial in a later feature request (about a year after the intial change). We were asked to provide a way to restore parts of the bar (when switching printheads between) with their previous data. Because we already had a way to probe the database and restore previous states of the system, it was fairly straightforeward to design and implement a procedure to identify the relevent history (using a differnt entry in the database) and restore the proper data from it. which we could then combine with the current data and avoid the need for a new calibration step (printing a special file and scanning the paper).

### Example - Cross Bars Operations
The seperation between the general handler and the individual bar handlers allowed us to implement features that analyzed the system as a whole. we could use the higher layer to identify similiraties between bars, which could indicate that the problem source is not the print heads (it's unlikely all bars have the same malfunctiong nozzles in same loccation), and it might be an issue with the sacnner or the blanket.  
[...]


## Technologies
We used C# for the business logic.  
The UI was built using WPF.  
Some testing was done using Postman and HTTP requests, mostly written in C#.
