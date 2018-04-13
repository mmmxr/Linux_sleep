.PHONY:clean
sleep:sleep.c
	gcc -o $@ $^
clean:
	rm -f sleep
