# Acac( Ammeliorated Complex Ackermann Control)

![Test Spac](https://github.com/FSLART/Spac/actions/workflows/test_wf.yaml/badge.svg)

Acac is a more complex version of https://github.com/FSLART/spac. A special thanks to Jordan from the barcelona formula student team (i should @ you in the future, but even though we're camping side by side i couldnt memorize your teams name).

This project is meant to be developed side by side with spac to ensure that if this control doesn't work it can be trashed and replaced with SPAC or more complex control algorithms("Linear Quadratic Regulator" or even the dreaded Model Predictive Control )

Uhh rereading the last line i should probs rechec documentation after every major push.(This commit should clear the previous error)

## Whats the preface

I really hate the pid controller, its too simple, boring
On software simulations a lerp function gave similar results and in real life i would guess someone would've lost a leg from the car trying to go straight.

## Whats it about

Like spac its a pid based controller but unlike spac, it uses self tuning PID to try to overcome the multiple faced challenges, like manual tuning for sharp corners, going straight, road conditions, etc...

### Why is there a bunch of spac references

\todo: change names of libraries...
The reason is twofold: first everytime i refactor is a pain in the ass and its currently 6 in the morning during FS Portugal Competition. I cant sleep...

## What this isnt about

1. **Fixing data crappy interfaces between Eletronics department and higher level software.**
2. **Giving the eletronics department something to work with(much like above)**
3. **Outputting "judge/rules" required data for things like minimum throughput(write something of a more synchronous nature)**

## Explain it in firmware terms

Basically the job that was asked, was cutting a weirdly shapped, ant filled patch of grass. Pid controller as usual is like a hammer and you can use it for pretty much any problem(even if the given solution isnt desired). We can wack the patch of grass all day long and basically make small modifications to the hammer and eventually all the ant tunnels and grass will either be smoshed into paste or turned into decaying matter.
IE yes i guess pid will get you to the finish line however, choosing a hammer that is efficient to all ant holes would take forever and there always that one hole that you slowly come to the realisation through its neighboors that you have to change the hammer. Not to mention we havent cut the grass.
For this we ran somewhat of an informed pid. Instead of just eyeballing the number or using a one time tunner. You change the gains by looking at the expected output. Or in very oversimplifed terms: a pid over a pid(i guess )

## Papers please

As always the research is largely based on a combination of watching something of the kind work and some few highlighted texts in a bunch of IEEE papers that i can acess through my Student branch account

UHh i read this for 10 seconds and the draft seems to have the correct words:

https://ieeexplore.ieee.org/document/9641467

## Setup ["native"]

The package requires diagnostic-updater, geographic_info, ackermann_msg, and angles package as such you will have to do a rosdep install

## Setup [Arch based]

```bash
paru -S ros2-humble-ackermann-msgs
```
