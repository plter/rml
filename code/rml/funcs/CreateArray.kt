package rml.funcs

import rml.cmds.Arg
import rml.Context
import rml.cmds.Var

class CreateArray(parent: Context?) : CreateMap(parent, "CreateArray", null) {

    class RMLArray {
        private val _arr = ArrayList<Var?>()
        private val _sizeVar = Var(null, 0, null, null, 0, "CreateArray.kt")

        fun add(item: Var?) {
            _arr.add(item)
        }

        fun get(index: Int): Var? {
            return _arr[index]
        }

        fun size(): Var {
            _sizeVar.value = _arr.size
            return _sizeVar
        }

        override fun toString(): String {
            return "RMLArray($_arr)"
        }
    }

    class GetItemFunc(parent: Context?) : Func(null, null, parent) {
        override fun execute(args: List<Arg>): Var? {
            if (args.size == 1) {
                return ArrayTools.getRMLArray(target)?.get((args[0].value as? String)?.toInt()!!)
            } else {
                error("Array.getItem requires 1 arg")
            }
        }
    }

    class AddItemFunc(parent: Context?) : Func(null, null, parent) {
        override fun execute(args: List<Arg>): Var? {
            ArrayTools.getRMLArray(target)?.add(args[0])
            return null
        }
    }

    class GetSizeFunc(parent: Context?) : Func(null, null, parent) {
        override fun execute(args: List<Arg>): Var? {
            return ArrayTools.getRMLArray(target)?.size()
        }
    }


    override fun execute(args: List<Arg>): Var? {
        val v = super.execute(args)
        val arr = RMLArray()
        for (a in args) {
            arr.add(a)
        }

        val rmlMap = MapTools.getRMLMap(v)
        rmlMap?.set("__bound_array__", Var(null, arr, null, parent, 0, "CreateArray.kt"))
        rmlMap?.set("getItem", Var(null, GetItemFunc(parent), null, parent, 0, "CreateArray.kt"))
        rmlMap?.set("addItem", Var(null, AddItemFunc(parent), null, parent, 0, "CreateArray.kt"))
        rmlMap?.set("size", Var(null, GetSizeFunc(parent), null, parent, 0, "CreateArray.kt"))

        return v
    }

    object ArrayTools {
        fun getRMLArray(target: Var?): RMLArray? {
            return (((target?.value as? RMLMap)?.get("__bound_array__") as? Var)?.value as? RMLArray)
        }
    }
}