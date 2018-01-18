package rml.funcs

import rml.cmds.Arg
import rml.Context
import rml.cmds.Call
import rml.cmds.Var

open class CreateMap(parent: Context?, name: String? = "CreateMap", ns: String? = null) : Func(name, ns, parent) {

    class RMLMap {
        private val _map = HashMap<String, Var?>()
        val map: HashMap<String, Var?> get() = _map

        fun set(key: String, value: Var?) {
            map[key] = value
        }

        fun get(key: String): Var? {
            return map[key]
        }

        override fun toString(): String {
            return map.toString()
        }
    }

    class SetFunc(parent: Context?) : Func(null, null, parent) {
        override fun execute(args: List<Arg>): Var? {
            if (args.size == 2) {
                MapTools.getRMLMap(target)?.set(args[0].asString()!!, args[1])
            } else {
                error("Map.set requires two args")
            }
            return null
        }
    }

    class GetFunc(parent: Context?) : Func(null, null, parent) {
        override fun execute(args: List<Arg>): Var? {
            if (args.size == 1) {
                return MapTools.getVar(args[0].asString()!!, target)
            } else {
                error("Map.get requires 1 arg")
            }
        }
    }

    override fun execute(args: List<Arg>): Var? {
        val map = Var(null, RMLMap(), null, parent, 0, Constants.fileId)
        MapTools.setVar("set", SetFunc(parent), map)
        MapTools.setVar("get", GetFunc(parent), map)

        return map
    }

    object MapTools {
        fun getRMLMap(target: Var?): RMLMap? {
            return target?.asRMLMap()
        }

        fun getVar(key: String, target: Var?): Var? {
            return getRMLMap(target)?.get(key)
        }

        fun setVar(key: String, value: Var?, target: Var?) {
            getRMLMap(target)?.set(key, value)
        }

        fun setVar(key: String, value: Any?, target: Var?) {
            setVar(key, Var(null, value, null, target, 0, Constants.fileId), target)
        }

        fun callFunc(funcName: String, to: String?, targetName: String?, args: List<Arg>, target: Var?): Var? {
            val c = Call(funcName, to, targetName, target, 0, Constants.fileId)
            c.target = target
            for (a in args) {
                c.addArg(a)
            }
            return c.execute()
        }
    }

    object Constants {
        const val fileId = "CreateMap.kt"
    }
}