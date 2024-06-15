**Materialized Locks** (Table of Locks). 
	_...Meetings Rooms Slot booking example..._

Table of dummy rows created ahead of time. You acquire lock only on the row you target.

eg: meeting room booking. 
Create dummy rows for each slot for each room ... _ahead of time_ .


_What is the use?_
Helps get rid of [[concurrency bugs#Phantom Writes|Phantom Writes]] ..where you don't even have rows to begin with, where will you put the locks if you rows don't yet exist??
- you want to honor an invariant "meeting room is booked by atmost 1 person"
- you make a read to confirm the invariant is not broken
- you insert a row to "book" the slot
	- (_meanwhile another TXN inserts a similar row to book the same slot_)
- Invariant is now broken
- If you wanted to use LOCKs to solve this problem, rows did not even exist in the first place to apply the LOCK on them.

