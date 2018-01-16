package rml

import rml.cmds.Command
import rml.cmds.Return
import rml.cmds.Var
import rml.funcs.Func

open class Scope(parent: Scope?) {

    private val _parent: Scope? = parent
    val parent: Scope? get() = _parent

    private val _funcs = HashMap<String, Func>()
    val funcs: HashMap<String, Func> get() = _funcs

    private var _varsStatus = HashMap<String, Var>()
    val varsStatus: HashMap<String, Var> get() = _varsStatus

    private var _commands = ArrayList<Command>()
    val commands: List<Command> get() = _commands


    fun addFunc(func: Func) {
        _funcs[func.fullyQualifiedName!!] = func
    }

    fun addCommand(cmd: Command) {
        _commands.add(cmd)
    }

    fun getFunc(fullyQualifiedName: String): Func? {
        val f = funcs[fullyQualifiedName]
        if (f != null) {
            return f
        } else {
            if (parent != null) {
                return parent?.getFunc(fullyQualifiedName)
            } else {
                return null
            }
        }
    }


    fun getVar(name: String): Var? {
        val v = varsStatus[name]
        if (v != null) {
            return v
        } else {
            if (parent != null) {
                return parent?.getVar(name)
            } else {
                return null
            }
        }
    }

    fun setVar(variable: Var?) {
        if (variable != null) {
            _varsStatus[variable.name!!] = variable
        }
    }

    fun getRoot(): Scope? {
        if (parent != null) {
            return parent?.getRoot()
        } else {
            return this
        }
    }

    open fun execute(args: List<Arg>): Var? {
        _varsStatus = HashMap()

        for (c in commands) {
            val result = c.execute()
            if (c is Var) {
                setVar(result)
            } else if (c is Return) {
                return result
            }
        }
        return null
    }
}