Message bus system (IPC) for applications to communicate with each other, popularly used within Desktop Environments like GNOME, KDE, to listen to system wide events
- "device inserted" / "removed"
- power events
- network events

eg: 
- when we change the volume in the sound applet, the sound applet sends a message over DBus to sound daemon to adjust volume.
- when a USB drive is inserted, the file manager sends a message over DBus to system daemon to mount the drive.
- when we click on network icon, a message is sent over DBus to NetworkManager to show the list of WIFI networks.


DBus is more efficient than RPC since it uses **async message passing**. 

DBus uses a client-server architecture. The server is the message bus, the clients send and recv messages.
