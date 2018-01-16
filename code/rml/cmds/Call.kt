package rml.cmds

import rml.Arg
import rml.Scope
import rml.funcs.CreateMap
import rml.funcs.Func

class Call(funcName: String, to: String?, target: String?, parent: Scope?, lineNum: Int, fileId: String) : Command(parent, lineNum, fileId) {
    private val _funcName: String = funcName
    val funcName: String get() = _funcName

    private val _args = ArrayList<Arg>()
    val args: ArrayList<Arg> get() = _args

    private val _targetName: String? = target
    val targetName: String? get() = _targetName

    private val _to: String? = to

    fun addArg(arg: Arg) {
        _args.add(arg)
    }

    override fun execute(): Var? {
        val target = if (targetName != null) {
            getVar(targetName!!)
        } else {
            null
        }
        val f: Func? = if (target != null) {
            ((target.value as? CreateMap.RMLMap)?.get(funcName) as? Var)?.value as? Func
        } else {
            getFunc(funcName)
        }
        if (f != null) {
            f.target = target
            val result = f.execute(args)
            if (_to != null) {
                val toVar = getVar(_to)
                if (toVar != null) {
                    toVar.value = result?.value
                } else {
                    if (result != null && parent != null) {
                        val variable = Var(_to, result.value, null, parent, lineNum, fileId)
                        parent?.setVar(variable)
                    }
                }
            }
        } else {
            error("Function $funcName not found at line $lineNum in file $fileId")
        }
        return null
    }
}