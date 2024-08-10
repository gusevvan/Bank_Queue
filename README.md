# Bank_Queue
 An application that accepts json as input with information about bank departments and clients and simulates client processing.

## JSON format
The application expects input in the following json format:
```
{ "departments": [
    {
        "name": "name of department1",
        "employees": num of employees in deparment1
    },
    ...
    {
        "name": "name of departmentN",
        "employees": num of employees in departmentN
    }],
  "clients": [
    {
        "name": "name of client1",
        "time": time needed to serve client1 in ms,
        "priority": priority of client1 (1-5),
        "departments": [
            "name of first department that client1 come",
            ...
            "name of last department that client1 come"
        ]
    },
    ...
    {
        "name": "name of clientM",
        "time": time needed to serve clientM in ms,
        "priority": priority of clientM (1-5),
        "departments": [
            "name of first department that clientM come",
            ...
            "name of last department that clientM come"
        ]
    }]
}
```

## Build application.
To build an application, first create a build directory. To do this, run the following somewhere not in the project directory:
```
$ mkdir name_of_build_directory
```
Then change to the created build directory by:
```
$ cd name_of_build_directory
```
And build project using cmake (you must have cmake version 3.22 or higher installed):
```
$ cmake path_to_project
$ make
```

## Run application.
After building the project, the bank_queue application will appear in the build directory. To run it use the following in your build directory:
```
$ ./bank_queue path_to_input_json
```
