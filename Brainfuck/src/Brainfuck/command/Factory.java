package Brainfuck.command;


import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

/**
 * Factory construct commands
 */
public final class  Factory {
    private static Logger log = LogManager.getLogger(Factory.class.getName());

    /**
     * Config file with commands
     */
    private Properties config = new Properties();
    /**
     * Hashmap. key = symbol , value = class command;
     */
    private Map<Character, Class<Command>> commands = new HashMap<>();

    /**
     * Construct Factrory with certain config
     * @throws RuntimeException
     * @param configPath path to config file
     */
    public Factory(String configPath) {
        log.info("Construct factory");
        if(log.isDebugEnabled()){
            log.debug("Path to properties file = " + configPath);
        }
        try (InputStream file = ClassLoader.getSystemResourceAsStream(configPath)) {
            config.load(file);
        } catch (IOException e) {
            log.error(e);
            //System.err.println("Cant open config file!");
            throw new RuntimeException(e);
        }

    }

    /**
     * Insert Class command to HashMap
     * @param name symbol
     */
    public void set(Character name) {
        if(log.isDebugEnabled()){
            log.debug("Charachter for special Brainfuck command =" + name);
        }
        try {
            Class command = Class.forName(config.getProperty(String.valueOf(name)));
            if (Command.class.isAssignableFrom(command)) {
                commands.put(name, command);
            }
        } catch (ClassNotFoundException e) {
            log.error(e);
            //System.out.print("Cant find class!");
            e.printStackTrace();
        }
    }

    /**
     * Get certain command
     * @param name command symbol
     * @return Object or null;
     */
    public Command get(char name) {
        if(log.isDebugEnabled()){
            log.debug("Special name for Brainfuck command = " + name);
        }
        if (!commands.containsKey(name)) {
            set(name);
        }
        try {
            return commands.get(name).newInstance();
        } catch (InstantiationException | IllegalAccessException e) {
            log.debug(e);
            //e.printStackTrace();
            return null;
        }
    }

}