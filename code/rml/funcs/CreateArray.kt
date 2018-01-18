package rml.funcs

import rml.cmds.Arg
import rml.Context
import rml.cmds.Call
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
                return ArrayTools.getRMLArray(target)?.get(args[0].asInt()!!)
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

        MapTools.setVar("__bound_array__", arr, v)
        MapTools.setVar("getItem", GetItemFunc(parent), v)
        MapTools.setVar("addItem", AddItemFunc(parent), v)
        MapTools.setVar("size", GetSizeFunc(parent), v)
        return v
    }

    object ArrayTools {
        fun getRMLArray(target: Var?): RMLArray? {
            return MapTools.getVar("__bound_array__", target)?.asRMLArray()
        }
    }

    object Constants {
        const val fileId = "CreateArray.kt"
    }
}