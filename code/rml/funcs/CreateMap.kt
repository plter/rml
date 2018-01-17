package rml.funcs

import rml.cmds.Arg
import rml.Context
import rml.cmds.Var

class CreateMap(parent: Context?) : Func("CreateMap", null, parent) {

    class RMLMap {
        private val _map = HashMap<String, Any?>()
        val map: HashMap<String, Any?> get() = _map

        fun set(key: String, value: Any?) {
            map[key] = value
        }

        fun get(key: String): Any? {
            return map[key]
        }

        override fun toString(): String {
            return map.toString()
        }
    }

    class SetFunc(parent: Context?) : Func(null, null, parent) {
        override fun execute(args: List<Arg>): Var? {
            if (args.size == 2) {
                (target?.value as? RMLMap)?.set(args[0].value as String, Var(null, args[1].value, null, parent, 0, "CreateMap.kt"))
            } else {
                error("Map.set requires two args")
            }
            return null
        }
    }

    class GetFunc(parent: Context?) : Func(null, null, parent) {
        override fun execute(args: List<Arg>): Var? {
            if (args.size == 1) {
                return (target?.value as? RMLMap)?.get(args[0].value as String) as? Var
            } else {
                error("Map.get requires 1 arg")
            }
        }
    }

    override fun execute(args: List<Arg>): Var? {
        val map = RMLMap()
        map.set("set", Var(null, SetFunc(parent), null, parent, 0, "CreateMap.kt"))
        map.set("get", Var(null, GetFunc(parent), null, parent, 0, "CreateMap.kt"))

        return Var(null, map, null, parent, 0, "CreateMap.kt")
    }
}