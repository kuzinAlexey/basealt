

SUBDIRS =	lib src 

all:
	$(MAKE) $(SUBDIRS)

$(SUBDIRS): FORCE
	if [ -d $@ ]; then cd $@ ; $(MAKE); fi

clean:
	for i in $(SUBDIRS); do ( if [ -d $$i ]; then cd $$i ; $(MAKE) $@; fi; ) ; done

install: 
	for i in $(SUBDIRS); do ( if [ -d $$i ]; then cd $$i ; $(MAKE) $@; fi; ) ; done

doc:
	for i in $(SUBDIRS); do ( if [ -d $$i ]; then cd $$i ; $(MAKE) $@; fi; ) ; done

deb:
	dpkg-buildpackage -rfakeroot -us -uc -j4 -i -I
	
FORCE:


