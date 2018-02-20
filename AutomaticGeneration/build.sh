export CLASSPATH=".:/usr/local/lib/antlr-4.7.1-complete.jar:$CLASSPATH"

java -jar /usr/local/lib/antlr-4.7.1-complete.jar Grammar.g4
javac Grammar*.java