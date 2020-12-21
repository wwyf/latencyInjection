# Inject latency with cycles level precision

Anyone interested in latency injection can read the code to get the details.

just:

```
sudo ./run.sh
```

## A Sample

I run it on my server with fixed frequency(2.3GHz). This injection method forms a stepped shape on this scatter plot since the overhead of `rdtsc` and `pause` is inevitable. And the minimum injection granularity is approximately 70 cycles ( ~30ns ).

![](./example.jpg)
