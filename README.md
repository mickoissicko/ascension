# ascension
Ascension to Heaven (ATH) is a shell.

# `.ath` scripts
Indeed this shell has its own shell scripting language!

Here's how it looks like:

```rb
via ath.
!indent_sz = 4
begin.
    include Std::IO.

    begin def start
        echo "Hello, world!\n".
    end
end.
```

`via ath` is used to define the interpreter.

`!indent_sz` is a standard variable. It is used to set how many spaces you will indent by, if any.

`begin.` starts the main program until `end.`

`include` is the directive used to enable modules. `Std::IO` is used for `echo` in our program.

`begin def start` is the entry point, like `int main()`.

Inside it, all the code is executed until `end`.

# style changed (?)
Yes, style has changed. I wrote this originally to pass time and challenged myself to obfuscate it as much as possible.

Then, I realised I could update Ascension.

So I quickly deobfuscated.

Will make consistent later.
