.PHONY: clean run out stats

subsystem:
	$(MAKE) -C ./serial/
	$(MAKE) -C ./parallel/

clean:
	rm -f out*
	$(MAKE) -C ./serial/ clean
	$(MAKE) -C ./parallel/ clean
	$(MAKE) -C ./analysis/ clean

run_serial: 
	$(MAKE) -C ./serial/ run

run_parallel:
	$(MAKE) -C ./parallel/ run

stats:
	$(MAKE) -C ./analysis/ stats

out:
	tail -f out
