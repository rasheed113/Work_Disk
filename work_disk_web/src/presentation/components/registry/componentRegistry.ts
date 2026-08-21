export type ComponentLayer='foundation'|'core'|'container'|'input-data'|'specialised'
export type ComponentRegistration={id:string;name:string;layer:ComponentLayer;eligible:boolean}
const definitions=[
['design-tokens','Design Tokens','foundation'],['typography','Typography','foundation'],['layout-primitives','Layout Primitives','foundation'],['responsive-primitives','Responsive Primitives','foundation'],['motion-primitives','Motion / Animation Primitives','foundation'],['surface-3d','Elevation / 3D Surface Primitives','foundation'],
['button','Button','core'],['icon-action','Icon Action','core'],['badge','Badge','core'],['avatar','Avatar','core'],['tooltip','Tooltip','core'],['divider','Divider','core'],['loading','Loading State','core'],['empty','Empty State','core'],['error','Error State','core'],
['card','Card','container'],['panel','Panel','container'],['section','Section','container'],['grid','Grid','container'],['stack','Stack','container'],['modal','Dialog / Modal','container'],['drawer','Drawer','container'],
['text-input','Text Input','input-data'],['select','Select','input-data'],['checkbox','Checkbox','input-data'],['toggle','Toggle','input-data'],['search','Search','input-data'],['filter','Filter','input-data'],['form','Form','input-data'],['list','List','input-data'],['table','Table','input-data'],
['profile','Profile Component','specialised'],['capability','Capability Component','specialised'],['notification','Notification Component','specialised'],['activity','Activity Component','specialised'],['media','Media Component','specialised'],['chat','Chat Component','specialised'],['feed','Feed Component','specialised'],['dashboard-card','Dashboard Card Infrastructure','specialised'],['cards-gallery','Cards Gallery Infrastructure','specialised'],
] as const
export const componentRegistry:readonly ComponentRegistration[]=definitions.map(([id,name,layer])=>({id,name,layer,eligible:true}))
export function getEligibleComponents(){return componentRegistry.filter(c=>c.eligible)}
