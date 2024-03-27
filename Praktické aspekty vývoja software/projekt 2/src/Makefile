MAIN=main.py
MATH_LIB=math_lib.py
MATH_TESTS=math_lib_tests.py
PROFILING=profiling.py
REQUIREMENTS=requirements.txt
ZIP=xbella01_xmatus35_xvrabl05

.PHONY:
	all
	pack
	test
	doc
	clean
	run
	profile
all: requirements run
	
requirements:
	python3 -m pip install -r $(REQUIREMENTS)

pack: doc installer clean
	mkdir -p ../../$(ZIP)/repo

	cp -r ../ ../../$(ZIP)/repo
	mv ../../$(ZIP)/repo/installer ../../$(ZIP)
	mv ../../$(ZIP)/repo/doc ../../$(ZIP)
	
	cd ../../ && zip -r $(ZIP).zip $(ZIP)
	rm -rf ../../$(ZIP)

clean:
	rm -rf __pycache__	
#TODO
test: $(MATH_TESTS)
	python3 -m pytest $(MATH_TESTS)

doc: Doxyfile
	doxygen Doxyfile

run: $(MAIN)
	python3 $(MAIN)

profile: $(PROFILING)
	python3 $(PROFILING) > ../profiling/vystup.txt

installer: 
	mkdir -p ../installer/usr/share/toJeJedno 2>/dev/null
	cp $(MAIN) ../installer/usr/share/toJeJedno/$(MAIN) && chmod +x ../installer/usr/share/toJeJedno/$(MAIN)
	cp $(MATH_LIB) ../installer/usr/share/toJeJedno/$(MATH_LIB)
	mkdir -p ../installer/usr/share/app-install/icons/toJeJedno
	cp icon.png ../installer/usr/share/app-install/icons/toJeJedno
	mkdir -p ../installer/usr/local/bin 2>/dev/null
	ln -sf /usr/share/toJeJedno/$(MAIN) ../installer/usr/local/bin/Calculator
	mkdir -p ../installer/tmp 2>/dev/null
	cp requirements.txt ../installer/tmp/requirements.txt
	mkdir -p ../installer/DEBIAN
	chmod 755 ../installer/DEBIAN
	echo "sudo apt-get install python3-pip" > ../installer/DEBIAN/postinst
	echo "python3 -m pip install -r ../tmp/$(REQUIREMENTS)" >> ../installer/DEBIAN/postinst
	chmod 755 ../installer/DEBIAN/postinst
	dpkg-deb --build ../installer/ ../installer/Calculator.deb