# Eras Support in Cuneiform

## Overview

**Eras** are a core Cuneiform feature that allows entities and worlds to change over time periods or story phases. They represent natural epochs at the world or entity level, enabling dynamic storytelling across different time periods.

## Types of Eras

### 1. World-Level Eras

Define major time periods or phases that affect the entire story world:

```cuneiform
@world_eras {
    - Colony Days: Early settlement period
      visual: struggling settlements, basic technology
      mood: desperate but hopeful
      
    - Golden Age: Period of prosperity  
      visual: thriving cities, advanced technology
      mood: optimistic and confident
      
    - Decline: Things fall apart
      visual: abandoned buildings, failing infrastructure  
      mood: melancholic and uncertain
}
```

### 2. Entity-Level Eras (Nested)

Define how individual entities change across story phases:

```cuneiform
@characters {
  - Hero: Main protagonist
    role: main_character
    @eras {
      act1: naive and idealistic
      act2: tested and doubting  
      act3: wise and determined
    }
    
  - Mentor: Guide character
    role: guide
    @eras {
      early: mysterious stranger
      middle: trusted advisor
      late: sacrificial hero
    }
}
```

### 3. Specialized Eras

For specific entity types:

```cuneiform
@character_eras {
  - Leadership transition phases
}

@location_eras {
  - Seasonal or environmental changes  
}

@entity_eras {
  - Generic entity evolution
}
```

## Grammar Support

The Cuneiform grammar now fully supports:

✅ **Top-level eras blocks**: `@world_eras {`, `@character_eras {`, etc.  
✅ **Nested eras within entities**: `@eras {` inside entity definitions  
✅ **Balanced brace parsing**: Proper handling of nested structures  
✅ **Flexible content**: Rich descriptions with metadata  

## Usage Patterns

### World Building
Use world-level eras to define major story periods:
- Historical epochs
- Technological ages  
- Environmental phases
- Political periods

### Character Development  
Use entity-level eras to show character growth:
- Personality evolution
- Skill development
- Relationship changes
- Role transformations

### Location Evolution
Track how places change over time:
- Seasonal variations
- Development stages
- Damage and repair
- Cultural shifts

## IDE Support

The VS Code/Cursor extension provides:
- ✅ Syntax highlighting for all eras patterns
- ✅ Proper parsing and error detection
- ✅ Code folding for era blocks
- ✅ IntelliSense support for era structures

## Examples

See these example files for eras in action:
- `examples/eras_demo.cune` - Comprehensive eras demonstration
- `examples/habitatable/world_with_inline_eras.cune` - Sci-fi world with rich eras
- `examples/syntax_demo.cune` - Eras within entity definitions

## Benefits

Eras enable:
1. **Dynamic storytelling** across time periods
2. **Character development** tracking  
3. **World evolution** over story arcs
4. **Template flexibility** for different story phases
5. **Rich world-building** with temporal depth

Eras are essential for complex storytelling and are now fully supported in the Cuneiform grammar and tooling! 🎭