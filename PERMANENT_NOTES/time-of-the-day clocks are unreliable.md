
You want to **_order_** the writes. 
[[version vectors to detect concurrent writes|version vectors]] only tell you that so and so writes are _concurrent_, but which of them came first ?

#### Time-of-the-day clocks are unreliable
Timestamps seem like a great simple way to resolve conflicts across nodes. Can you depend on timestamps? You need clocks. Can you depend on the regular quartz time-of-the-day clocks?: NO

Each machine has its own (quartz) clock, actual h/w device. Not accurate. It _drifts_ based on machine temperature(6ms drift every 30s, 17s per day). Needs to be synced via NTP (adjusting self time via time reported by a group of NTP servers). PTP(Precision Time Protocol) is a costlier NTP.
> **Note**: Clocks in VMs
> CPU is essentially "paused" for tens of milliseconds for a given VM. time may suddenly seem to _jump_ from the applications' point of view.

> **Note**: NTP sync is not accurate too
> NTP synchronization accuracy is itself limited by network round trip time.
- Local Quartz Clocks usually _synchronize_ with a NTP Server.
- Sync happens periodically (say every 2 hours)
- Quartz clock **DRIFT**: 
	- If you don't sync, then you have have a _drift of 7 seconds per day_.
- You cannot really control the sync on devices controlled by users (PC, mobile devices)

If these happen, you cannot really depend on such clocks. They cannot even order the events properly, let alone telling the accurate timestamp. Schemes like LWW(Last Write Wins) will become extremely ambiguous since the "actual" last write might be processed before another write because the machine's clock was lagging by 7 seconds.

_**Just use a monotonic (logical) clock**_ (Lamport Clock)
- you don't need actual timestamps.
- Relative ordering of events is enough.

You have 2 types of Clocks:
- **Time of the day Clocks**: To give you exact timestamp since epoch.
	- number of milliseconds since epoch.
	- NOT guaranteed to always move forward.
	- can move forward or backward. "jumping forward in time".
	- Hence need to be synced via NTP
	- unsuitable to measure "elapsed time(duration)".
- **Monotonic Clocks**(Logical Clocks): To measure durations.
	- guaranteed to always move forward.
	- absolute value of this clock is meaningless. (might be numberof nanoseconds since computer started).
	- There may be one monotonic clock per CPU.
	- NO need for syncing with NTP.
	- **Logical Clocks**(Lamport Clock)
		- neither absolute time nor duration(elapsed time)
		- _it measures relative order of events_
		- whether one event happened before or after another.


#### Ordering Events
_Ordering of events across multiple nodes, each with their own clock_

You cannot depend on TimeOfTheDay clocks for this, **You need logical clocks**(Lamport Clock).
![[ddia-41.png]]
Here, when a write is replicated to other nodes, the write is "tagged" with a timestamp according to the time-of-the-day clock on the node where write originated. But the ordering of writes(events) isn't correct, see image above. LWW (Last Write Wins) is applied and you actually lose the "last write" as per absolute time, just because a node had its clock jumped slightly ahead. **Actual Latest data is being silently dropped without any error being reported!**. Definition of "recent" depends on the local time-of-the-day clock 

Solution? Logical Clocks (Lamport Clock) which depends on monotonically increasing counters, instead of absolute timestamps.

**Confidence Intervals**
_Used by google's TrueTime API_

Since clocks can never be _really_ accurate, its better to include the error , or the "range" of times..with a confidence interval _(earliest,latest)_. The exact time is somewhere within the interval.
Say you have 95% confidence that the time now is between (10.3,10.5).
The width of the interval depends on how long it has been since the local quartz clock was last synced with a more accurate clock ( since it drifts ).


>**Note**: Some DBs actually still use time-of-the-day clock timestamps to resolve conflicts: eg: **cassandra**., **spanner**.  They encourage you to keep all your nodes synchronized with NTP as much as possible(frequent).


#### Lamport Clock
TODO