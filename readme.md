### Workflow
1.  opening file, checking if its intact 
2.  looking for the main file (jpeg or png)
3.  comparing current position with the file size,
    - if values match, then there is no archive present -> Printing, Cleaning and Exiting (1)

    - if file size is larger, then program assumes the archive is in the file
    
4.  (?) extracting main file
5.  looking for all localfileheaders (lfh) in the file
6.  after lfh type is read printing the filename using the lfh filesize field
7.  Printing, Cleaning and Exiting (2)

### Run

`make all`

by default will check all files in ./assets directory 

