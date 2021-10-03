# Missing Nozzles Refactor

## Actors

- dps subsystem: manager, handler, accessor
- qcs,test driver and other external subsystems
- database
- missing nozzles handler, missing nozzles bar handlers, missing nozzles helper class

## What are missing Nozzles?

In a printing system, each color is mounted on a bar. each bar contains printing heads, each printing head contains nozzles. the nozzles are what 'shoots' out the ink. a nozzle is a hole that's about a pixel wide, and it can be damaged, shifted, malfunction in all kinds of ways.  
If a nozzle isn't working properly, we can compensate for it using it's neighbors, they can pick up the slack for it.  
our module was designed to handle this situation: we identify which nozzles to compensate for, based both on raw data and according to decision algorithms.

## Requirements - Why did we change the system

The previous system relied on external sources to make the decisions, it was simply a pipe between the raw data and the controller. it wasn't able to validate complex data, identify possible problems in the data (it might be corrupted), and to account for different expectations for printing quality (customer A might require much higher printing quality than customer B).  
The refactor was meant to allow us to meet new requests and to prepare an infrastructure for future demands.

## Parts

All parts of the program can interact with the **database** (get and set parameters), some of them are notified when parts of it are changed.

The **manager** receives information from any number of external subsystems, this layer controls the exposed API.
The **handler** interacts with the manager, this layer embodies the business logic of the program
The **accessor** interacts with the manager, this layer communicates with the controller.

the handler and accessor contain respective bar handlers and bar accessors. each bar corresponds to a color. the bar handlers control the business logic that is independent from other bars, while the main handler requests and aggregates the responses from the bar handlers, and controls the business logic that relates to more than one bar. any number of components can reuse this structure, without getting in the way of other modules (_the main bar handlers control the printing activity_).

following the design described above, we have a single **missing nozzles handler** and several **missing nozzles bar handlers**. Those classes contain the actual logic relating to missing nozzles operations.  
The **missing nozzles helper** component controls operations relating to mediating between the form the data is stored in the database (a byte array that has been encoded to reduce its' size) and the runtime form (an object that contains 50k nozzle objects).

## Basic Flow

- receive a correction / calibration data regarding missing nozzles. this is a snapshot of the current state of the machine.
  - online correction from a different subsystem.
  - corrections from a file.
  - manual corrections from the ui.
  - exposed API from the testing project.
- analyze the incoming data compared to the existing data, perform corrections as needed.
  - replacing or adding data.
  - validating data.
  - which algorithms are used.
- decide whether to accept the new data or reject it.
  - accept or reject all the data (all bars) or some of them.
  - if reject, restore system to previous state.
- handle the result (reject or accept).
  - forward the accepted data.
  - respond with a detailed explanation of the rejection reason.

## design patterns?

- Decorator/Chain of responsibility - some algorithms could be used together or apart, but they had to be sequential. so we built objects with decorator levels, so if some algorithm isn't needed, we don't build that layer.
- Builder - we separated the construction/storage/retrieval logic from the usage logic.
- Adapter/Facade - transform the different forms of incoming data into a common form. account for missing data (from UI) but still use the same behavior.
- Memento - eventually, we could restore the state of the system back to a different time (not perfect example).
- CRTP (curios recursive template pattern) - save some typing, reduce some duplication in derived class.

## My contribution

The refactor started as a team project (four people), with the design decisions being done by the team leader and the senior developer. my initial role was the handling the logging and exporting of data, implementing the cross bars logic in the missing nozzles handler (aggregate results from the bars), and creating the tests for the changes.  
As the project continued and we received more requests for changes and features (more algorithms, differentiation between customers, concerns about storage), I got involved with more and more of the module. eventually, I had to write a guide and present it to the team when I left the job.

### Example - Database Operations

In the old system, there was no mechanism to say if the correction was a failure or success, if we received data and we could parse it into the database, it was a success. if we failed, it was an indication of either a programming bug or one of the subsystems was offline. in the refactored system, we needed to apply validation on the data integrity.  
If one bar failed, we might decide to roll back the entire operation, which would require probing the database and rebuilding the object (multiple requests to a shared object with it's own locks). We solved this issue by separating the data from the class, so each object held a copy of the data stored by the database, and could rebuild itself from it independently. So at any point during the correction, we could command a bar to restore itself to the last acceptable state.  
This ability proved crucial in a later feature request (about a year after the initial change). We were asked to provide a way to restore parts of the bar (when switching print heads in the same bar) with their previous data. Because we already had a way to probe the database and restore previous states of the system, it was fairly straightforward to design and implement a procedure to identify the relevant history (using a different entry in the database) and restore the proper data from it. which we could then combine with the current data and avoid the need for a new calibration step (printing a special file and scanning the paper).

### Example - Cross Bars Operations

The separation between the general handler and the individual bar handlers allowed us to implement features that analyzed the system as a whole. we could use the higher layer to identify similarities between bars, which could indicate that the problem source is not the print heads (it's unlikely all bars have the same malfunctions nozzles in same location), and it might be an issue with the scanner or the blanket.  
we had to account for factors like the source of information, the current configuration, the amount of new data, and user parameters to be able to give an estimate of the situation. each bar produced an appropriate span of ranges, and the high level handler collapsed those spans to identify common areas and report them. in one case we could simply report them after the fact, or even reject the changes and maintain our state.

## Technologies

We used C# for the business logic.  
The UI was built using WPF.  
Some testing was done using Postman and HTTP requests, later automated into the testing suite using C#.
