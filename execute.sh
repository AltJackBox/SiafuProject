#!/bin/sh

#for i in {1..10}; do rm ressources/CalculatedGradients/Simulation-Office/*; time ./bin/Simulation -s; done

for i in {1..10}; do rm $HOME/.Siafu/CalculatedGradients/Siafu\ Offices/* ; time /home/yael/2019/share/jdk/bin/java -Xmx500m -Dfile.encoding=UTF-8 -classpath /home/yael/Bureau/Cours/S9/STAGE/Siafu/Siafu/target/classes:/home/yael/.m2/repository/commons-collections/commons-collections/3.2.1/commons-collections-3.2.1.jar:/home/yael/.m2/repository/commons-configuration/commons-configuration/1.6/commons-configuration-1.6.jar:/home/yael/.m2/repository/commons-digester/commons-digester/1.8/commons-digester-1.8.jar:/home/yael/.m2/repository/commons-beanutils/commons-beanutils/1.7.0/commons-beanutils-1.7.0.jar:/home/yael/.m2/repository/commons-beanutils/commons-beanutils-core/1.8.0/commons-beanutils-core-1.8.0.jar:/home/yael/.m2/repository/commons-logging/commons-logging/1.1.1/commons-logging-1.1.1.jar:/home/yael/.m2/repository/commons-lang/commons-lang/2.6/commons-lang-2.6.jar:/home/yael/.m2/repository/org/eclipse/swt/org.eclipse.swt.gtk.linux.x86_64/4.5/org.eclipse.swt.gtk.linux.x86_64-4.5.jar:/home/yael/.m2/repository/swt/jface/3.0.1/jface-3.0.1.jar:/home/yael/.m2/repository/swt/runtime/3.0.1/runtime-3.0.1.jar:/home/yael/.m2/repository/swt/osgi/3.0.1/osgi-3.0.1.jar de.nec.nle.siafu.control.Siafu --simulation=/home/yael/Bureau/Cours/S9/STAGE/Siafu/Simulation-Office/target/Simulation-Office-1.0.6-SNAPSHOT.jar -s; done
