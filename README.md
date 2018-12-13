# safecracking-firstalert
Building and designing a robot to open a safe with an unknown combination.

Link to photo and video documenation: http://bit.ly/first-alert-documentation

Try times:
100 possible numbers for 3 disks:
100x100x100 = 1,000,000 combinations
Each number can be +/- 1
Not likely or possible to duplicate numbers between disks
33x32x32 = 34,848
13 seconds per test means 5.25 days (without set testing)

We know the disks were only moved around and the first and last disk cannot move.
This means that the first number of the combination has to be 97 and the last must be 0.
1x33x32 = 1,056 combinations
13 seconds per test means 3.81 hours (without set testing)

After looking at the disks inside the safe we saw that they were split into 17 equal, numbered sections where interference points were placed.
The disk closest to the door had one interference point at 9 facing inward towards the safe.
The second two disks were identical and had interference points at 7 on one side and 3 on the other.
Then the disk farthest from the door had an interference point at 10 facing outward towards the door.
We know that the two middle disks are identical and only have two orientations.
We also know that the first and last disks cannot move or be changed.
So we have four possible orientations of the disks and their interference points.
(9)(7/3)(7/3)(10),
(9)(7/3)(3/7)(10),
(9)(3/7)(7/3)(10),
(9)(3/7)(3/7)(10).

This means there are only four possible combinations, one of which is the old one, so in reality, three possible combinations.
(97,32,44,0),
(97,32,??,0),
(97,??,44,0),
(97,??,??,0).

We can guess that most likely both middle disks were flipped to create more mystery
If we find which orientation the old disks were we can model the new orientation and find a range where the missing numbers could be so that we can make our blunt force test WAY faster than 4 hours. Ideally we should find a range of 10 or 15 which would be 3 to 5 set tests.
1x3x3 = 2 minutes
1x5x5 = 5.5 minutes

Even if we settled for finding a range of 48 values (figuring out right/left numbers of dial or top/bottom numbers of dial) it would be 16 tests.
1x16x16 = 55 minutes

Even though we ended up testing only 4 possible combinations, the blunt force test time for the right one (97, 7, 67) would be
1x2x50 = 25 minutes (testing up until getting the correct second number) + 1x1x34 = 8.5 minutes (last test with correct second number until reaching the correct 3rd number).
Being a total of 33.5 minutes to find this particular combination with our tests checking every other number to make up for any slop in the system.
