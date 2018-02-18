import org.antlr.v4.runtime.ANTLRInputStream;
import org.antlr.v4.runtime.CommonTokenStream;

import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        Scanner s = new Scanner(new File("./input.txt"));
        String code = "";
        while (s.hasNext()) {
            code += s.nextLine() + "\n";
        }
        GrammarParser parser = new GrammarParser(null);
        parser.setBuildParseTree(false);
        ANTLRInputStream input = new ANTLRInputStream(code);
        GrammarLexer lexer = new GrammarLexer(input);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        parser.setInputStream(tokens);
        System.out.println(parser.code().res);
    }
}