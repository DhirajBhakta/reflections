#kubernetes  #storage #pv #pvc

>**Info**
> PVC is NOT deleted when a Pod is deleted.
> Deletion of the PVC is manual.
> Even if you delete the PVC, the PV **may** survive, depending on the **ReclaimPolicy** set on the PV

PVC is meant to **survive** Pod restarts to provide **data persistence**

_a PVC is first bound to a PV...and then the PVC is bound to a Pod._
Death of a Pod will not break the bond between the PVC and the PV. 

### PVC to PV binding
If the `VolumeBindingMode` of the PV is "WaitForFirstConsumer", then the PVC will NOT be attached to the PV. Later when a Pod is created, associating to the PVC, at that moment, the PVC gets bound to the PV.

If the `VolumeBindingMode` of the PV is "Immediate", then the PVC immediately binds to the PV...without needing a Pod to be created.
### Deletion of the PVC is manual
When a Pod dies, the PVC survives (PV survives too). The binding between the PVC and PV is **not broken**. Data is not lost. When another Pod is created which references this PVC, it gets all the data written by the previous Pod. Similar to how EBS is unaffected if the EC2 is killed. "Peristent" Volume for a reason.

_You have to manually delete the PVC_. And even then, the data in the PV survives if the `ReclaimPolicy` is set to "Retain" on the PV.

Sometimes, PVC wont be deleted when you try to delete it. This is for **protected PVC**. There are **Finalizers** set on the PVC. remove the finalizers and then you can delete the PVC

