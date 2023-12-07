Red/System [
  title: "Melvin Shell"
]
system/words: load %system.red
print "Welcome to the Melvin Shell."
print "© 2023 Dr. Cat"
print "Type 'l8r' to quit."
current-dir: system/user/user-data/current-dir
forever [
    user-input: ask rejoin [current-dir " ⤗ "]
    if user-input = "l8r" [
        print "Thank You, Come Again!"
        quit
    ]
    if parse user-input ["cd" any space copy new-dir to end] [
        new-dir: trim/all new-dir
        if exists? new-dir [
            current-dir: new-dir
            change-dir current-dir
        ] else [
            print rejoin ["Directory not found: " new-dir]
        ]
        next
    ]
    if parse user-input [some copy commands some ["|" copy next-command]] [
        result: none
        foreach command commands [
            user-input: command
            result: do user-input
        ]
    ] [
        result: do user-input
    ]
    either error [
        print ["Error:" mold error]
    ][
        print ["Result:" mold result]
    ]
]
